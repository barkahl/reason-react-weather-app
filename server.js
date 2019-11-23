const express = require('express');
const proxy = require('express-http-proxy');
const { stringify } = require('querystring');
const URL = require('url');

const app = express();

const API_URL = 'https://api.weatherstack.com';

if(process.env.NODE_ENV === 'production') {
    app.use(express.static('./build'))
} else {
    const webpack = require('webpack');
    const webpackDevMiddleware = require('webpack-dev-middleware');
    const config = require('./webpack.config.js');

    const compiler = webpack(config);

    app.use(webpackDevMiddleware(compiler, {
        publicPath: config.output.publicPath,
    }));
}

app.use('/api', proxy(API_URL, {
    proxyReqPathResolver: req => {
        const { pathname, query } = URL.parse(req.url);

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
            access_key: process.env.WEATHER_STACK_API_KEY,
        })}`;
    },
}));

const PORT = process.env.PORT || 3000;
app.listen(PORT, function () {
    console.log(`App listening on port ${PORT}!\n`);
});
