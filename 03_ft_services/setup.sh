#!/bin/sh

# Before launching this script, make sure that docker, minikube
# and hyperkit are installed:
# https://hub.docker.com/editions/community/docker-ce-desktop-mac
# https://minikube.sigs.k8s.io/docs/start/
# https://minikube.sigs.k8s.io/docs/drivers/hyperkit/

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RESET="\033[0m"

f_check_img() {
    # 1 = service/image name
    if [[ $(docker image ls | grep $1) ]]
    then
        printf "${GREEN} - $1 successfully created\n${RESET}"
    else
        printf "${RED} - failed to create $1; exiting\n${RESET}"
        exit 1
    fi
}

minikube status &> /dev/null
if [ $? -eq 7 ]; then
    printf "${YELLOW}❖ Cleaning up existing Minikube profile\n${RESET}"
    minikube stop
    minikube delete
fi

printf "${YELLOW}❖ Starting Minikube\n${RESET}"
minikube start --driver=hyperkit
printf "${YELLOW}❖ Enabling addons\n${RESET}"
minikube addons enable metrics-server
minikube addons enable dashboard &> /dev/null
echo "🌟  The 'dashboard' addon is enabled"
minikube addons enable metallb

printf "${YELLOW}❖ Setting IP address in yaml files\n${RESET}"
LC_ALL=C find ./srcs/yamls -type f  -exec sed -i "" "s|$(cat srcs/yamls/last_saved_minikube_ip.txt)|$(minikube ip)|g" {} +

eval $(minikube -p minikube docker-env)
printf "${YELLOW}❖ Building images\n${RESET}"
docker build -f srcs/Dockerfile.ftps -t ftps ./srcs/ &> /dev/null
f_check_img ftps
docker build -f srcs/Dockerfile.grafana -t grafana ./srcs/ &> /dev/null
f_check_img grafana
docker build -f srcs/Dockerfile.influxdb -t influxdb ./srcs/ &> /dev/null
f_check_img influxdb
docker build -f srcs/Dockerfile.mysql -t mysql ./srcs/ &> /dev/null
f_check_img mysql
docker build -f srcs/Dockerfile.nginx -t nginx ./srcs/ &> /dev/null
f_check_img nginx
docker build -f srcs/Dockerfile.phpmyadmin -t phpmyadmin ./srcs/ &> /dev/null
f_check_img phpmyadmin
docker build -f srcs/Dockerfile.wordpress -t wordpress ./srcs/ &> /dev/null
f_check_img wordpress

printf "${YELLOW}❖ Setting up volumes\n${RESET}"
kubectl create -f ./srcs/volumes/ &> /dev/null

printf "${YELLOW}❖ Configuring MetalLB\n${RESET}"
printf "${YELLOW}❖ Deploying services\n${RESET}"
kubectl apply -f ./srcs/yamls/ &> /dev/null

printf "${YELLOW}❖ Launching Minikube dashboard\n${RESET}"
minikube dashboard &

sleep 20

printf "${YELLOW}❖ Opening http://$(minikube ip):80\n${RESET}"
open "http://$(minikube ip):80"
