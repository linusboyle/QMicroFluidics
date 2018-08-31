# QMicroFluidics

QMicroFluidics is a Qt-based minimal designer for microfluidics.Its inner algorithm is based on Hailong Yao and Weiqing Ji's work,which is an extension of the original paper by Junchao Wang, Philip Brisk and William H. Grover.You can read the paper in the application or find it in the /resource directory

This program supports two languages:English and simplified Chinese.Its main feature includes:

- Easy-to-use UI,with selectable objects and elegant operation interface
- Taking advantage of Graphics View Framework of Qt, it is possible to zoom in/out,rotate smoothly
- Print the design directly or save as a .bmp,.jpg or .png file
- Colorize the pipe according to the velocity of liquid inside

## Dependencies

- Qt >=5
- c++11 compatible compiler

What follows is the design note in Chinese:

# 微流控生物芯片设计器

QMicroFluidics 是简洁、优雅的生物芯片模拟器，使用Qt作为图形前端。

- 自由的放大缩小、旋转视角，不再受制于传统的绘图方法
- 将设计图传递给打印机，或者简单地保存为图片。
- 可拖拽式的操作方法，设计更省心
- 英文/简体中文双语支持
- 遵循freedesktop桌面规范，让自定义图标美化窗口！(X11 only)
- 根据流速大小自动调整颜色，设计更加方便

## 编译依赖

- Qt >=5
- 符合C++11标准的编译器

## 开发手记

应用的开发严格遵循面向对象的模式，对于不满足这一要求的底层算法，同时进行了适当的包装。程序的核心是Qt强大的Graphics View框架，主窗体就是由Graphics View及自定义控制组件，以及底部的流速显示器组成

### 流速显示器

VelocityIndicator 基于QTableWidget,用于显示输入/输出流速。实例与程序的通信方式主要是信号槽：在清空画布时清空数据，在画布改变时更新数据

### 芯片编辑器

编辑器分为四个部分：视图窗口，缩放条及其控制按钮，旋转条及其控制按钮，重置按钮。EditorWidget使用GridLayout组合这四个部分。

四个部分之间相互关联，最终的表现在中央视图的状态上。首先是重置按钮，用于将视图重置为默认状态，此按钮只有在用户改变设置时可以被点击。完成这一需求的是两个控制条的valuechanged信号，在槽setupmatrix中，按钮将被激活，同时基于两个控制条的值缩放旋转中央视图。四个控制按钮起到辅助作用，本身没有交互能力，只是简单的重新设定控制条当前值，从而间接地改变视图属性。

编辑器的此部分封装对外暴露的接口是公用槽zoomin/zoomout/rotateleft/rotateright/resetview，这些槽被用于主窗体的菜单栏和工具栏中。

### 画布

画布是基于QGraphicsScene使用的。其内部通过读入设置体(即configurationentity)，自动设定新的绘制方式。由于其内部包含对设置体的deep copy，可以随时恢复到初始状态（即restore的实现方式）。画布对外暴露重置函数、deleteSelectionItems槽、restore槽。

删除管道实现只是很简单地将其设置为不可见状态。为了更方便地进行后续的操作（即计算流速），画布内维持一个QHash容器，通过哈希将管道的编号和指针相对应。

### 芯片计算服务器

即MicroFluidicsServer类。这是一个使用了单例模式的类，更方便在各实现文件调用。它将底部算法做了包装，不再暴露任何标准库的内容，并防止命名空间污染。主要接口queryVelocity，返回值被用作信号参数发出，用以规避返回tuple或者vector的尴尬场面。

另一接口queryNearItemsIndex提供了逻辑和数学上的方便，用于在设置宽度时判断是否满足距离大于200微米的要求。

### 管道

Pipe类只是简单的一个长方形而已，但重绘事件会根据Graphics View特有的状态，自动改变颜色和ZValue（即Z值，可以防止常见的管道相互重叠带来的颜色bug）。另外重写双击事件以改变宽度。

### 弹出窗口

没什么好说的，一些组件和布局的组合而已
