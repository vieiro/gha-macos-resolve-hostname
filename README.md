# GHA macos-13 getaddrinfo issues

This is a reproducer for GHA issue https://github.com/actions/runner-images/issues/8649

The function `getaddrinfo` was unable to resolve the result of `$(hostname -f)`. Note that this is usually a [`.local` address](https://en.wikipedia.org/wiki/.local) (such as `Mac-1721125139157.local`).

The **issue was solved in august 2024 and new deployed `macos-13` images in github do not have this problem now**.

The repository is being kept for future reference.

## Actions

This repo includes a simple GHA workflow that runs `getaddrinfo` on different platforms (`macos-13`, `ubuntu-latest`) and invokes it with both `'localhost'` and `$(hostname -f)`. You can then verify the results on each platform.

One of the jobs updates the `/etc/hosts` file, allowing `getaddrinfo` to properly resolve `$(hostname -f)`.


## Update 2024-08-21

Github claims that this is now solved. Let's try by adding a new commit to master and running GHA actions again...

## Update 2024-08-26

It seems the new Github builder images with a fix have been now deployed. Let's test them with a new commit & build.
