# :large_orange_diamond: ft_server &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/ft_server)

The aim of this project is to set up a web server using docker.

## :small_orange_diamond: Instructions

1. Make sure docker is installed.

2. Run `docker build -t image_name .` to build the image.

3. Run `docker run --name container_name -d -p 80:80 -p 443:443 image_name` to start the server.

## :small_orange_diamond: Useful Commands

Command | Description
:------:|:-----------:
`docker exec -it container_name /bin/bash` | opens bash in a running container
`sed -i "s/autoindex on/autoindex off/g" etc/nginx/sites-available/ft_server` | changes autoindex from on to off when inside the container
`sed -i "s/autoindex off/autoindex on/g" etc/nginx/sites-available/ft_server` | changes autoindex from off to on when inside the container
`service nginx restart` | to save the changes made 
`docker cp container_name:/src/path /dest/path` | copies a file from a running container to the host
`docker stop $(docker ps -aq)` | stops all running containers
`docker rm $(docker ps -aq)` | removes all containers
`docker rmi $(docker images -q)` | removes all images
`docker system prune -a` | removes all containers and all images not in use

## :small_orange_diamond: Resources
#### docker
- [Orientation and Setup](https://docs.docker.com/get-started/)
- [Best Practices for Writing Dockerfiles](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
#### Wordpress
- [How To Install WordPress with LEMP (Nginx, MariaDB and PHP) on Debian 10](https://www.digitalocean.com/community/tutorials/how-to-install-wordpress-with-lemp-nginx-mariadb-and-php-on-debian-10)
#### Nginx
- [How to Install Nginx on Debian 10](https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-debian-10)
- [Enabling the Nginx Directory Index Listing](https://www.keycdn.com/support/nginx-directory-index)
#### MySQL/MariaDB
- [How To Install MariaDB on Debian 10](https://www.digitalocean.com/community/tutorials/how-to-install-mariadb-on-debian-10)
- [Executing SQL Statements from a Text File](https://dev.mysql.com/doc/refman/8.0/en/mysql-batch-commands.html)
- [When Privilege Changes Take Effect](https://dev.mysql.com/doc/refman/5.7/en/privilege-changes.html)
#### phpMyAdmin
- [How To Install phpMyAdmin From Source on Debian 10](https://www.digitalocean.com/community/tutorials/how-to-install-phpmyadmin-from-source-debian-10)
#### SSL
- [How To Create a Self-Signed SSL Certificate for Nginx in Ubuntu 18.04](https://www.digitalocean.com/community/tutorials/how-to-create-a-self-signed-ssl-certificate-for-nginx-in-ubuntu-18-04)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
