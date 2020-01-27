FROM node:12
WORKDIR /usr/src/app

ADD . .

RUN npm ci --quiet && npm run compile

EXPOSE 8080

CMD ["node", "./dist/server.js"]
