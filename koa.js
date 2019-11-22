const config = require('./webpack.config.js');
const webpack = require('webpack');
const webpackDevMiddleware = require('webpack-dev-middleware');
const koaWebpack = require('koa-webpack');
const Koa = require('koa');
const server = require('koa-better-http-proxy');
const serve = require('koa-static');
const { stringify } = require('querystring');
const URL = require('url');

const API_BASE_URL = 'https://api.weatherstack.com';

const staticDirectory = process.env.NODE_ENV === 'production' ? './build' : './lib/js/src';

const app = new Koa();

const compiler = webpack(config);
const middleware = koaWebpack({
    compiler,
    config,
    devMiddleware: {
        publicPath: config.output.publicPath,
    },
    hotClient: false,
});

app.use(async () => await middleware);
app.use(serve(staticDirectory));

// app.use(koaWebpack(compiler, {
//     publicPath: config.output.publicPath,
// }));


app.use(server(API_BASE_URL, {
    proxyReqPathResolver: ctx => {
        const { pathname, query } = URL.parse(ctx.url);

        if (!query) {
            return;
        }

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
app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));
