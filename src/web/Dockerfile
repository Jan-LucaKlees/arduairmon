FROM python:3.7-alpine3.8
LABEL maintainer = "Jan-Luca Klees"

# Make everything fresh
# build-deps, gcc, python3-dev, musl-dev and postgresql-dev are needed for building and installing psycopg2
RUN apk update && apk upgrade && \
    apk add --virtual build-deps gcc python3-dev musl-dev && \
    apk add postgresql-dev

# pip
RUN pip install flask 'psycopg2==2.7.5' 'peewee==3.7.1'

# copy entrance point
COPY docker-entrypoint.sh /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh
ENTRYPOINT ["/docker-entrypoint.sh"]

# image config
WORKDIR /airmon

