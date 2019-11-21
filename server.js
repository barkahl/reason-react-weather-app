const Koa = require('koa');
const server = require('koa-better-http-proxy');
const serve = require('koa-static');
const { stringify } = require('querystring');
const URL = require('url');

const API_BASE_URL = 'https://api.weatherstack.com';

const app = new Koa();

app.use(serve('./build'));

app.use(server(API_BASE_URL, {
    proxyReqPathResolver: ctx => {
        const { pathname, query } = URL.parse(ctx.url);

        const splitQuery = query.split('&');
        const params = splitQuery.reduce((acc, param) => {
            const [key, value] = param.split('=');
            return {
                ...acc,
                [key]: value,
            };
        }, {});

        return `${pathname}?${stringify({
            ...params,
            access_key: process.env.WEATHERSTACK_API_KEY,
        })}`;
    },
}));

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => console.log(`Proxy server listening on port ${PORT}`));
