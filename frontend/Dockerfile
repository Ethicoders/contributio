# FROM node:alpine
FROM node:latest

COPY package.json /app/package.json

RUN yarn global add parcel-bundler

WORKDIR /app

ENV PATH /app/node_modules/.bin:$PATH

RUN yarn
