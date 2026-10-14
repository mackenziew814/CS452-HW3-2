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
  int pid = 0;
  for (int i=0; i<sizePipeline(r) && !*eof; i++)
    pid = execCommand(deq_head_ith(r->processes,i),pipeline,jobs,jobbed,eof,1);
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
