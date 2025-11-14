# GHA macos-15 getaddrinfo issues

This is a reproducer for GHA issue https://github.com/actions/runner-images/issues/12562

The function `getaddrinfo` was unable to resolve the result of `$(hostname -f)`. Note that this is usually a [`.local` address](https://en.wikipedia.org/wiki/.local) (such as `Mac-1721125139157.local`).

## Actions

This repo includes a simple GHA workflow that runs `getaddrinfo` on different platforms (`macos-15-intel`, `ubuntu-latest`) and invokes it with both `'localhost'` and `$(hostname -f)`. You can then verify the results on each platform.

One of the jobs updates the `/etc/hosts` file, allowing `getaddrinfo` to properly resolve `$(hostname -f)`.

## Update 2025-11-14

Upgrading from `macos-13` to `macos-15-intel`.

- `macos-13` GHA runner issue - solved - https://github.com/actions/runner-images/issues/8649
- `macos-15-intel` GHA runner issue - open - https://github.com/actions/runner-images/issues/12562

## Update 2024-08-21

Github claims that this is now solved. Let's try by adding a new commit to master and running GHA actions again...

## Update 2024-08-26

It seems the new Github builder images with a fix have been now deployed. Let's test them with a new commit & build.
