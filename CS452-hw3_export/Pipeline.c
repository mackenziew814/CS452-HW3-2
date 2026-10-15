#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Pipeline.h"
#include "deq.h"
#include "error.h"

typedef struct {
  Deq processes;
  int fg;			// not "&"
} *PipelineRep;

extern Pipeline newPipeline(int fg) {
  PipelineRep r=(PipelineRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->processes=deq_new();
  r->fg=fg;
  return r;
}

extern void addPipeline(Pipeline pipeline, Command command) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_tail_put(r->processes,command);
}

extern int sizePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  return deq_len(r->processes);
}

static int execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
  PipelineRep r=(PipelineRep)pipeline;
  int n=sizePipeline(r);
  // create n-1 pipes 
  int (*fds)[2]=0;
  if (n>1) {
    fds=malloc((n-1)*sizeof(*fds));
    if (!fds) ERROR("malloc() failed");
    for (int i=0; i<n-1; i++)
      if (pipe2(fds[i],O_CLOEXEC)==-1) ERROR("pipe2() failed"); //O_CLOEXEC so unused ends auto-close on exec
  }
  int pid=0;
  for (int i=0; i<n && !*eof; i++) {
    int pin  = (i>0)   ? fds[i-1][0] : -1;
    int pout = (i<n-1) ? fds[i][1]   : -1;
    pid=execCommand(deq_head_ith(r->processes,i),pipeline,jobs,jobbed,eof,r->fg,pin,pout);
  }
  // parent closes all pipe ends
  for (int i=0; i<n-1; i++) { close(fds[i][0]); close(fds[i][1]); }
  if (fds) free(fds);
  return pid;
}

extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
  PipelineRep r=(PipelineRep)pipeline;
  int jobbed=0;
  int pid = execute(pipeline,jobs,&jobbed,eof);
  if (jobbed && r->fg && pid>0)
    waitpid(pid,NULL,0);           // wait for foreground child to finish
  if (!jobbed)
    freePipeline(pipeline);	// for fg builtins, and such
}

extern void freePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_del(r->processes,freeCommand);
  free(r);
}
