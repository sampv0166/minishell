#ifndef EXECUTOR_h
#define EXECUTOR_h

#include "env_var.h"

typedef struct  s_pars_tokens
{
   char **cmd;         //       "ls" "-la" NULL // cat out2 out3 out4
   char *cmd_full;     //       "ls la |"
   char **cmd_splitted;//       "ls" "-la" "|" NULL
   int  pipe;          //       pipe_type (1, 2, 3)

   int  is_in;         //       if there is a input redirection
   int  is_out;        //       if there is a ouput redirection
   int is_out_appnd;   //       if there is a output append redirection

   int  fd_in;         //      file descriptor number for fd in
   int  fd_out;        //       file descriptor for fdout
   int  here_doc;      //       file descriptor for fd append

   int pipe_read_end;  //       fd for pipe read end
   int pipe_write_end; //       fd for pipe write end

   //
   // t_redir dskfg

} t_pars_tokens ;





#endif

