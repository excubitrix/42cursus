# :large_orange_diamond: ft_services &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/ft_services)

The objective of this project is to get familiar with Kubernetes by creating a multi-service cluster, using locally build images.

## :small_orange_diamond: Instructions

1. Make sure [docker](https://hub.docker.com/editions/community/docker-ce-desktop-mac), [minikube](https://minikube.sigs.k8s.io/docs/start/) and [hyperkit](https://minikube.sigs.k8s.io/docs/drivers/hyperkit/) are installed.
	- You can check this by running the following command in your terminal:
	```
	which docker minikube hyperkit
	```
	- If any are missing, they can be installed via homebrew:
	```
	brew install docker minikube hyperkit
	```

2. Execute the `setup.sh` script to launch the cluster.
```
./setup.sh
```

## :small_orange_diamond: Useful Commands

Command | Description
:------:|:-----------:
`kubectl exec -it <container_name> -- /bin/sh` | opens sh in a running container
`minikube start` | starts a local Kubernetes cluster
`minikube stop` | stops a local Kubernetes cluster (keeps user data intact)
`minikube delete` | deletes a local Kubernetes cluster (removes all associated files)

## :small_orange_diamond: Resources
#### Docker
- [Docker on Max w/ homebrew - A Step By Step Guide](https://www.cprime.com/resources/blog/docker-on-mac-with-homebrew-a-step-by-step-tutorial/)
- [Best Practices for Writing Dockerfiles](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
#### Kubernetes & Minikube
- [Hello Minikube](https://kubernetes.io/docs/tutorials/hello-minikube/)
- [Kubernetes Tutorial for Beginners](https://www.youtube.com/watch?v=X48VuDVv0do)
- Persistent Volumes
	- [Run a Single-Instance Stateful Application](https://kubernetes.io/docs/tasks/run-application/run-single-instance-stateful-application/)
- Liveness Probes
	- [Configure Liveness, Readiness and Startup Probes](https://kubernetes.io/docs/tasks/configure-pod-container/configure-liveness-readiness-startup-probes/)
	- [Bash Check Whether a Process is Running](https://www.cyberciti.biz/faq/bash-check-if-process-is-running-or-notonlinuxunix/)
#### MetalLB
- [Installation Via Minikube Addon](https://medium.com/faun/metallb-configuration-in-minikube-to-enable-kubernetes-service-of-type-loadbalancer-9559739787df)
- [Configuration](https://metallb.universe.tf/configuration/)
- [Usage](https://metallb.universe.tf/usage/)
#### NGINX
- [Understanding Server and Location Blocks](https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms)
- [Configuring HTTPS Servers](http://nginx.org/en/docs/http/configuring_https_servers.html)
- [NGINX Reverse Proxy](https://linuxize.com/post/nginx-reverse-proxy/)
- [Redirection in NGINX](https://www.hostinger.com/tutorials/nginx-redirect/)
- [Fix: Reserve Proxy to phpMyAdmin Returns 404 Not Found](https://serverfault.com/questions/931849/nginx-reverse-proxy-to-phpmyadmin-returns-404)
#### MySQL
- [MySQL Data Definition Statements](https://dev.mysql.com/doc/refman/8.0/en/sql-data-definition-statements.html)
- [Tutorial: How to Enable SSL and Remote Connections for MySQL](https://www.howtoforge.com/tutorial/how-to-enable-ssl-and-remote-connections-for-mysql-on-centos-7/)
#### phpMyAdmin
- [Configuration](https://docs.phpmyadmin.net/en/latest/config.html)
- MySQL
	- [Enable SSL for MySQL Connection](https://docs.phpmyadmin.net/en/latest/config.html#cfg_Servers_ssl)
- NGINX Server
	- [Single-Server-Block-Fix: HTTP Request to HTTPS Server Returns 400 Bad Request)](https://serverfault.com/questions/338700/redirect-http-example-com12345-to-https-example-com12345-in-nginx)
#### WordPress
- [Importing and Exporting Databases](https://www.marcbacon.com/how-to-easily-import-and-export-wordpress-mysql-databases-using-the-command-line-linux/)
- MySQL
	- [Enable SSL for MySQL Connection](https://www.monolune.com/how-to-connect-from-wordpress-to-mysql-using-ssl/)
#### InfluxDB & Grafana
- [Tutorial: How to Install TIG (Telegraf, InfluxDB, and Grafana) Stack](https://www.howtoforge.com/tutorial/how-to-install-tig-stack-telegraf-influxdb-and-grafana-on-ubuntu-1804/)
#### FTPS
- [Installation Guide](https://www.howtoforge.com/tutorial/how-to-install-and-configure-vsftpd/)
- [Configure SSL/TLS](https://netstudy.zlabs.be/28-configure-vsftpd-with-ssltls/)
- [vsftpd.conf Manual](http://vsftpd.beasts.org/vsftpd_conf.html)
#### Script
- [Bash Scripting Cheatsheet](https://devhints.io/bash)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### Attributions
- Dynamically generated badge by [badge42](https://github.com/JaeSeoKim/badge42)
