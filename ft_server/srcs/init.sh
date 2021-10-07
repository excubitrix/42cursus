# Config access
chown -R www-data /var/www/*
chmod -R 755 /var/www/*

# Generate website folder
mkdir /var/www/ft_server /var/www/ft_server/phpmyadmin

# SSL
openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/ssl/certs/nginx-selfsigned.crt -keyout /etc/ssl/private/nginx-selfsigned.key -subj "/C=BE/ST=Brussels/L=Brussels/O=19OU=floogman/CN=ft_server"

# Config NGINX
mv nginx_conf /etc/nginx/sites-available/ft_server
ln -s /etc/nginx/sites-available/ft_server /etc/nginx/sites-enabled/ft_server
rm /etc/nginx/sites-enabled/default

# Config MYSQL
service mysql start
mysql < mysql-config.sql
rm mysql-config.sql

# Untar phpmyadmin
tar -C /var/www/ft_server/phpmyadmin -xvzf phpMyAdmin-5.0.2-english.tar.gz --strip-components=1
mv phpmyadmin.inc.php /var/www/ft_server/phpmyadmin/config.inc.php
rm phpMyAdmin-5.0.2-english.tar.gz

# Untar wordpress
tar -C /var/www/ft_server/ -xvzf wordpress-5.4.2.tar.gz
mv wp-config.php /var/www/ft_server/wordpress
rm wordpress-5.4.2.tar.gz

service php7.3-fpm start
service nginx start

tail -f /var/log/nginx/access.log /var/log/nginx/error.log
