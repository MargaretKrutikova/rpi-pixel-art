FROM node:12
WORKDIR /usr/src/app

ADD . .

RUN npm ci --quiet && npm run compile

EXPOSE 8080
EXPOSE 8999

CMD ["node", "./dist/server.js"]
