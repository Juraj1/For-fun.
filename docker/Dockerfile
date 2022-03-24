# Author:   Jiri Zahradnik
# Date:     11.3.2022

FROM rabbitmq:3.8-management-alpine

ADD init.sh /init.sh
RUN chmod +x /init.sh

CMD ["/init.sh"]
