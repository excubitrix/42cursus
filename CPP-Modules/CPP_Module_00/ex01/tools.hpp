#ifndef TOOLS_H
# define TOOLS_H

# include <iostream>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"

void	put_welcome_msg(void);
void	put_else_msg(void);
void	put_goodbye_msg(void);
int		put_eof_msg(void);

#endif
