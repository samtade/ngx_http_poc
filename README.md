# Nginx http module with Go

This repository is made for playing [VS Code Remote development](https://code.visualstudio.com/docs/remote/remote-overview) and nginx custom module. I encourage you to download [VS Code Insider](https://code.visualstudio.com/insiders/) and try this remote development feature. It's really cool 😎

## Prerequisite
1. Install docker 

## Get started
1. Start VS Code and setup for remote development
2. Pressing `⇧⌘B` or running Run Build Task
3. Let's hacking 🐑

## Folder structure
```
|-- .devcontainer
    |-- .devcontainer.json      // dev container config
    |-- Dockerfile              // dev container's dockerfile
|-- .vsocde                     // vscode config
    |-- tasks.json
|-- docker                      // dockerfile
|-- nginx
    |-- nginx.conf              // conf loaded by nginx
|-- src
    |-- libngx_go_poc.go        // go lib to use in C
    |-- ngx_http_poc_module.c   // glue between nginx and go
```
