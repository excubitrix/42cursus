# :large_orange_diamond: webserv &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/webserv)

|   |   |
|:-:|:-:|
<img width="1700" alt="webserv" src="https://user-images.githubusercontent.com/59726559/136910177-efdf7931-e1e4-47e4-a459-0419eadf3a82.png"> | Team Member<br/><a href="https://github.com/magalifabri"><sub><br><img src="https://avatars.githubusercontent.com/u/65071369?v=4" alt="mfabri" width="250"/><br/></sub><sub><b>mfabri</b></sub></a> |

Webserv is a group project for teams of two to three students. Its objective is to write an HTTP server.

## :small_orange_diamond: Instructions

1. (optional) Setup a website in the `www/` directory and create a matching configuration file in the `config/` directory.

1. Run `make` to compile the program.

2. Launch the server with the name of the configuration file from the `config/` directory you wish to use as first argument. (If no configuration file is specified, `default.conf` will be used.)
```
./server config.conf
```

4. Open up [Chrome](https://www.google.com/intl/en/chrome/) and navigate to `localhost:<your_port>`.

## :small_orange_diamond: Config File

The syntax of the configuration file is inspired by [NGINX's configuration file](https://www.nginx.com/resources/wiki/start/topics/examples/full/).

Supported directives are:

Directive | Main/HTTP Context | Server Context | Location Context (Non-CGI) | Location Context (CGI) |
:---------|:-----------------:|:--------------:|:--------------------------:|:----------------------:|
server { ... } | ✅ | ❌ | ❌ | ❌
location \<name\> { ... }<br>&emsp;&emsp;&emsp;&emsp;.\<cgi_extension\> { ... } | ❌ | ✅ | ❌ | ❌
listen [\<hostname\>:]\<port\>; | ❌ | ✅ | ❌ | ❌
server_name \<name\> ...; | ❌ | ✅ | ❌ | ❌
root \<path\>; | ❌ | ✅ | ✅ | ✅
index \<name\> ...; | ❌ | ✅ | ✅ | ✅
accepted_methods \<method\> ...; | ❌ | ❌ | ✅ | ✅
cgi_pass \<path\>; | ❌ | ❌ | ❌ | ✅
autoindex on\|off; | ❌ | ✅ | ✅ | ✅
client_max_body_size \<size\>; | ❌ | ✅ | ✅ | ✅
error_page \<status_code\> ... \<path\>; | ❌ | ✅ | ✅ | ✅
upload_path \<path\>; | ❌ | ✅ | ✅ | ✅
return \<status_code\> [[http://<hostname>:<port>]/\<path\>];<br>&emsp;&emsp;&emsp;[http://<hostname>:<port>]/\<path\>; | ❌ | ✅ | ✅ | ✅

## :small_orange_diamond: Resources
- [Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
- [Example: Nonblocking I/O and select()](https://www.ibm.com/docs/en/i/7.1?topic=designs-example-nonblocking-io-select)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
- [Check Emoji](https://emojipedia.org/check-mark-button/)
- [Cross Emoji](https://emojipedia.org/cross-mark/)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
