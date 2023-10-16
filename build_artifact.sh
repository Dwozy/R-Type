#!/bin/bash

./build_unix.sh

mkdir -p ./artifacts/client
mkdir -p ./artifacts/server

cp -r R-Type/assets ./artifacts/client

cp R-Type/r-type_client ./artifacts/client
cp R-Type-server/r-type_server ./artifacts/server

echo '#!/bin/bash

IFS="/" read -r -a array <<< "$SHELL"
shell=${array[${#array[@]}-1]}

echo "export PATH=\"$(pwd):$PATH\"" >> ~/."$shell"rc
' > ./artifacts/server/install.sh

chmod +x ./artifacts/server/install.sh
cp ./artifacts/server/install.sh ./artifacts/client

find . -name "*.so" -exec cp {} ./artifacts/client \;
find . -name "*.so" -exec cp {} ./artifacts/server \;

zip artifacts/r-type_client_linux_x86-64.zip ./artifacts/client/*
zip artifacts/r-type_server_linux_x86-64.zip ./artifacts/server/*
