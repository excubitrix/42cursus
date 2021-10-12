## CONFIG CHECKS

### change error page
1. show http://localhost:8080/subdir_POST/ in the browser
2. uncomment error page directive in config file in location /subdir_POST
3. show http://localhost:8080/subdir_POST/ again

### limit client body (& uploading with POST)
- test with just short enough body
curl -v -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data "................................................................................................100|"
- test with too long body
curl -v -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data ".................................................................................................101|"



## BASIC CHECKS

### get upload in browser
- show http://localhost:8080/subdir_DELETE/upload1 in the browser

### get upload with GET via curl
curl -X GET localhost:8080/subdir_DELETE/upload1

### extra: HEAD
curl -X HEAD -I localhost:8080/subdir_DELETE/upload1

### delete upload with DELETE
curl -X DELETE localhost:8080/subdir_DELETE/upload1

### bad (unimplemented) method (501 Not Implemented)
curl -X TRACE -I localhost:8080

### bad (forbidden) method (405 Method Not Allowed)
curl -X POST -I localhost:8080

### extra: PUT
curl -X PUT localhost:8080/subdir_PUT/newfile --data "Hello There"
curl -X PUT localhost:8080/subdir_PUT/newfile --data "Cya"



## BROWSER CHECKS (chrome)

- wrong url (404)
- list directory
