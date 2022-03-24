#!/bin/bash

# Author:   Jiri Zahradnik
# Date:     11.3.2022

( rabbitmqctl add_user $RABBITMQ_DEFAULT_USER $RABBITMQ_DEFAULT_PASSWORD 2>/dev/null; \
  rabbitmqctl set_user_tags $RABBITMQ_USER administrator; \
  rabbitmqctl set_permissions -p / $RABBITMQ_USER ".*" ".*" ".*" ; \
  echo "*** User '$RABBITMQ_DEFAULT_USER' with password '$RABBITMQ_DEFAULT_PASSWORD' completed. ***" ; \
  echo "*** Log in the WebUI at port 15672 (example: http:/localhost:15672) ***") &

rabbitmq-server $@
