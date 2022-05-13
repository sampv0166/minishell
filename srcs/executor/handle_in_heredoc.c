#include "../../includes/mini_shell.h"

extern t_env_var env;


void find_input_fd(t_pars_tokens  *pa_tkns,int i)
{
    int len;
    int j;
    int fd;
    
    len = get_2d_arr_len(pa_tkns[i].cmd_splitted);
    j = len;
    fd = 0; 
    while(pa_tkns[i].cmd_splitted && pa_tkns[i].cmd_splitted[j] && j >=0)
    {  
        if(pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<')
        {
            if(ft_strlen(pa_tkns[i].cmd_splitted[j]) == 1)
                break;
            else
            {
                env.fd_in = pa_tkns[i].here_doc_fd;
                env.open_heredoc_fdin = pa_tkns[i].here_doc_fd;
                break;  
            }
        }
        j--;
    }
}

int check_for_input_files(t_pars_tokens *pa_tkns, int i)
{
    int j;
    j = 0;
    find_cmd (pa_tkns, i, &j);
    while(pa_tkns[i].cmd_splitted && pa_tkns[i].cmd_splitted[j])
    { 
        increment_j(pa_tkns, i, &j);
        if(pa_tkns[i].cmd_splitted[j] &&  (pa_tkns[i].cmd_splitted[j][0] == '<' || pa_tkns[i].cmd_splitted[j][0] == '>'))
            continue;
        else if(pa_tkns[i].cmd_splitted[j])
        { 
            
            if(access(pa_tkns[i].cmd_splitted[j], F_OK) == 0)
                return(1);
            else
            {
                j++;
                continue; 
                exit(0);   
            }
        }
        else
            break;
    }
  
    return (0);
}

int open_fds(char **cmd_split, int i, int *fd_out, int *fd_in)
{
    if (cmd_split && cmd_split[i] && (cmd_split[i][0] == '>' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1]))
    {
        close_redir_fd(fd_out);
        *fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (*fd_out == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file"));
    }
    if (cmd_split[i] && (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' && ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1]))
    {
        close_redir_fd(fd_out);    
        *fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
        if (*fd_out == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file")); 
    }
    if (cmd_split[i][0] == '<' && ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1])
    {
        close_redir_fd(fd_in);    
        *fd_in = open(cmd_split[i + 1], O_RDONLY);
        if (*fd_in == -1)
            return (ft_perror(EXIT_FAILURE, "error opening file"));
    }
    return (0);
}

int open_files_fd(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
    int i;
    int fd_out;
    int fd_in;
    
    i = 0;
    fd_out = 0;
    fd_in = 0;
    while (cmd_split[i])
    {
        if(open_fds(cmd_split, i , &fd_out,&fd_in))
            return (EXIT_FAILURE);
        i++;
    }
    if(pa_tokens[tkn_idx].is_out)
    {
        env.open_fd_out = fd_out;
        env.fd_out = fd_out;
    }
    if(pa_tokens[tkn_idx].is_in)
    {
        env.open_fd_in = fd_in;
        env.fd_in = fd_in;     
    }
    
    return (0);
}

int handle_in_and_here_doc(t_pars_tokens *pa_tkns, int i)
{ 
    
    if (open_files_fd(pa_tkns[i].cmd_splitted, pa_tkns, i) == EXIT_FAILURE)
    {
        return (1);  
    }
    if (!check_for_input_files(pa_tkns, i))
    {
        find_input_fd(pa_tkns, i);
        env.fd_in = dup(env.fd_in);     
    }
    return (0);
}