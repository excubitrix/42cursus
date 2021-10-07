# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floogman <floogman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/20 14:31:22 by floogman          #+#    #+#              #
#    Updated: 2020/11/16 13:52:00 by floogman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster
COPY ./srcs ./
RUN apt-get update && apt-get install -y \
	mariadb-server \
	nginx \
	openssl \
	php-fpm php-mbstring php-mysql
CMD bash init.sh
