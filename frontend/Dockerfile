FROM node:23-slim

COPY package.json /app/package.json

RUN yarn add --dev parcel

WORKDIR /app

ENV PATH=/app/node_modules/.bin:$PATH

RUN yarn
