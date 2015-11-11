make && chmod +x ./dest/serve

./dest/serve -r ./public/ -p 9000 &
curl 127.0.0.1:9000/index.html

