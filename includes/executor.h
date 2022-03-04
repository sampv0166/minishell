#ifndef EXECUTOR_h
#define EXECUTOR_h

#include "env_var.h"






typedef struct  s_pars_tokens
{
   char **cmd;
   char *cmd_full;
   char **cmd_splitted;
   int  pipe;
   int  is_in;
   int  is_out;
   int is_out_appnd;
   int  fd_in;
   int  fd_out;
   int  here_doc;
} t_pars_tokens ;


void executor(char **tokens, t_env_var *var, t_pars_tokens *pa_tkns);

#endif

