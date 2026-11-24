# usage

下载qmk源码，在`layouts/community/60_ansi`克隆该仓库即可

```
# keychron v4
make keychron/v4/ansi:qmk_paradoxskin

# anne pro 2
make annepro2/c18:qmk_paradoxskin

# qk61
make qk61:qmk_paradoxskin
```

qk61烧录方法：按住esc插usb，然后会有一个U盘接入电脑，直接把elf放进那个文件夹里，再等磁盘消失即可

PS: qmk无法向下兼容，直接使用最新版本有编译失败的风险，当前适配节点
7e8690ea
