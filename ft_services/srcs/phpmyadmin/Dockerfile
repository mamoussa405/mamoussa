FROM alpine
RUN apk update
RUN apk add php7-common php7-iconv php7-json php7-gd php7-curl \
 && apk add php7-xml php7-mysqli php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql \
 && apk add php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap \
 && apk add php7-ctype php7-dom \
 && apk add php php-fpm php-session php-mbstring php-gettext
WORKDIR /usr/share/webapps/
RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.0.1/phpMyAdmin-5.0.1-all-languages.zip \
 && unzip phpMyAdmin-5.0.1-all-languages.zip \
 && rm phpMyAdmin-5.0.1-all-languages.zip \
 && mv phpMyAdmin-5.0.1-all-languages phpmyadmin \
 && chmod -R 777 /usr/share/webapps/ 
COPY config.inc.php  /usr/share/webapps/phpmyadmin/
RUN chmod 444 /usr/share/webapps/phpmyadmin/config.inc.php 
EXPOSE 5000
ENTRYPOINT php -S 0.0.0.0:5000 -t /usr/share/webapps/phpmyadmin