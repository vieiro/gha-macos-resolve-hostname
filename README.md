# GHA macos-13 getaddrinfo issues

This is a reproducer for GHA issue https://github.com/actions/runner-images/issues/8649

The function `getaddrinfo` is unable to resolve the result of `$(hostname -f)`.

Note that this is usually a [`.local` address](https://en.wikipedia.org/wiki/.local) (such as `Mac-1721125139157.local`).

## Actions

This repo includes a simple GHA workflow that runs `getaddrinfo` on different platforms (`macos-13`, `ubuntu-latest`) and invokes it with both `'localhost'` and `$(hostname -f)`. You can then verify the results on each platform.

One of the jobs updates the `/etc/hosts` file, allowing `getaddrinfo` to properly resolve `$(hostname -f)`.


