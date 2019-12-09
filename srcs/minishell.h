/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:10:34 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/21 15:43:01 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# define TRUE                   	1
# define FALSE                  	0
# define MAX_LEN_PATH           	10000
# define MAX_LEN_TEMP_STR       	10000
# define MAX_LEN_EXEC_PATH      	10000
# define MAX_LEN_STR_FOR_PIPE   	10000
# define MAX_LEN_BUFFER_TEMP    	10000
# define SPACE_BEFORE        		0
# define CHAR_BEFORE         		1
# define PROMPT              		"==========> minishell "
# define PROMPT_QUOTE				"dquote> "
# define INITIAL_PATH				"/Users/mabois"

typedef struct s_env_var	t_env_var;
typedef struct				s_echo
{
	int						to_line;
	int						s_quote;
	int						d_quote;
	int						i;
}							t_echo;
typedef struct				s_redir
{
	int						sq;
	int						dq;
	char					c;
	char					temp[MAX_LEN_TEMP_STR];
}							t_redir;
struct						s_env_var
{
	char					*var_name;
	char					*var_value;
	t_env_var				*next;
};
typedef struct				s_export
{
	char					name[10000];
	char					value[10000];
	struct s_export			*next;
}							t_export;
typedef struct				s_all
{
	int						in_exec;
	int						ctrd;
	int						pdes_cpy[2];
	int						stdin_cpy;
	int						s_q;
	int						d_q;
	int						x_q;
	char					*input;
	char					current_path[MAX_LEN_PATH];
	int						start;
	int						end;
	char					mod;
	t_export				*env;
	char					exec_path[MAX_LEN_EXEC_PATH];
	char					temp_str_1[MAX_LEN_TEMP_STR];
	char					temp_str_2[MAX_LEN_TEMP_STR];
	char					temp_str_3[MAX_LEN_TEMP_STR];
	char					**cp_argv;
	char					**arg_exec;
	int						pipe_fd[2];
	int						last_is_pipe;
	int						last_is_echo;
	int						last_is_rdr;
	int						ret;
	int						bks;
	int						pos[500];
	char					str_for_pipe[MAX_LEN_STR_FOR_PIPE];
	int						new_line_signal;
	int						no_prompt;
	struct stat				sb;
	t_env_var				*g_env_var;
}							t_all;
t_all						g_all;
int							ft_bt_echo(t_all *all);
int							ft_bt_export(t_all *all);
int							ft_bt_cd(t_all *all);
int							ft_parse_quote_cd_cut_1(t_all *all,
							char *mod, int *i, int *j);
int							ft_parse_quote_cd_cut_2(t_all *all,
							char *mod, int *i, int *j);
int							ft_parse_quote_cd_cut_3(t_all *all,
							char *mod, int *i, int *j);
int							ft_parse_quote_cd_cut_4(t_all *all,
							char *mod, int *i, int *j);
int							ft_parse_quote_cd_cut_5(t_all *all,
							char *mod, int *i, int *j);
void						ft_init_temp_str(t_all *all, int id);
void						ft_clear_arg_exec(t_all *all);
void						ft_init_str_for_pipe(t_all *all);
int							ft_init_all(t_all *all);
void						ft_lstclear(t_export **lst);
int							ft_strlen(char *str);
void						ft_putstr(char *str);
char						*ft_new_empty_string(void);
char						*ft_add_char(char **str, char c);
int							ft_compare_str(char *str_1, int limit, char *str_2);
void						ft_input_to_temp_str(t_all *all, int mod);
int							is_char(char c, int quotes);
void						ft_strcpy(char *dst, char *src);
void						ft_execve_child(t_all *all, int pdes[2], int *fd);
void						ft_execve_father(t_all *all, int pdes[2],
char						buffer_temp[MAX_LEN_BUFFER_TEMP], int *fd);
void						ft_execve_init_all(t_all *all);
int							ft_execve(t_all *all, int fd);
void						ft_create_exec_path(t_all *all);
int							ft_get_number_arg_exec(t_all *all);
char						*ft_create_one_arg_exec(t_all *all,
							int arg_number, int i);
void						execve_error(t_all *all);
int							ft_create_arg_exec_init(t_all *all,
							int *i, int *mod, int *arg_number);
void						ft_exit(int num);
void						ft_clean_all(t_all *all);
void						ft_exit_final(t_all *all);
void						ft_exit_final_2(int num);
int							init_data(t_all *all);
int							wrong_identifier(int i, t_all *all);
int							ft_strcmp(char *s1, char *s2);
void						delete_double(t_all *all);
int							print_env(t_all *all);
int							unset(t_all *all);
int							ft_strcmp(char *s1, char *s2);
void						remove_env(char *s, t_all *all);
void						create_file(t_all *all);
char						*write_ret(t_all *all);
int							print_env_error(t_all *all, int i);
void						env_write(t_export *temp);
int							quote_error(void);
int							ft_is_end_char(char c);
void						ft_check_commas_init(int *i, char *c);
void						ft_get_input_init(t_all *g_all,
							char **input, char *last);
char						*ft_get_input(t_all *g_all, int ret, char last);
int							print_env_export(t_all *all);
int							check_export(t_all *all);
void						ft_bt_pwd(t_all *all);
void						ft_check_commas_init(int *i, char *c);
int							ft_check_commas(void);
void						backslash(void);
int							ft_search_exec_path(t_all *all, int i,
							int j, int k);
void						ft_init_exec_path(t_all *g_all);
int							ft_search_exec_path_abs_rel(t_all *g_all);
int							save_env(int i, t_all *g_all);
int							ft_bt_export_path(t_all *g_all);
int							set_mod(int i);
void						ft_quote_cut(t_all *g_all);
int							new_term(char *buffer);
int							new_term(char *buffer);
int							ft_parse_quote_cd(t_all *g_all, int i);
void						set_path(t_all *g_all);
void						ft_exit_final_3(int num);
int							ft_only_space(t_all *g_all, int i, char mod);
void						ft_put_space_in_arg(t_all *g_all, char replace);
void						ft_put_tab(t_all *g_all);
char						set_separator(int *i, t_all *g_all);
#endif
