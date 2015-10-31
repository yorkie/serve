
# serve

A tiny(~140kb) server(executable) for serving static files without any runtime like Python/Node.js/Ruby required.

## Why I create this

Sometimes I hope to deliver document or website to someone, which runtime/machine is not the Mac and installed Python,
Node.js and etc., Yea, the file protocol doesn't not address the relative and absolute path issue, because the file
protocol would depend strongly on what the machine's folders structure, hence, I created this tiny cross-platform
executable to run html files in HTTP protocol without any runtime required.

## Usage

> Currently this only supports OSX

```
$ dest/serve -r [dir] -p [port]
```

- `-r` the directory to serve, default directory is the relative path `./public`.
- `-p` specify the port to listen, default is 8000.

## Downloads

All available downloads are here: https://github.com/yorkie/serve/releases

## Build

```
$ make
```

## Author

- [@yorkie](https://github.com/yorkie)

## Thanks

Thanks to [@cesanta](https://github.com/cesanta) to create the awesome open source library [mongoose](https://github.com/cesanta/mongoose).

## License

GPLv2
