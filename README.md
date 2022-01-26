# Clocky

A tiny tool to help you integrate different qt widgets

## Usage

Compile in your environment or use the release in windows.

## Development

1. Create your own class, and your top class should be derived from QWidget.

2. Add your .pri to Clocky.

3. Choose your widget's sidebar icon, and add it to qt resources "sidebaroption".

4. Add some code in widget.cpp. Like

   ```cpp
   *** = new ***(stkWidget);
   addOption(QColor(YOUR FAVOURITE COLOR), "ICON NAME IN 3.", "PROJECT NAME", ***);
   ```

   Example:

   ```CPP
   // 时钟
   digitalclock = new DigitalClock(stkWidget);
   addOption(QColor(240, 124, 130), "clock.png", "时钟", digitalclock);
   ```

5. Run and cheer

   > The project is in your system tray.

## TODO

### Clocky

1. add more settings
2. enable the resize of widget
3. sidebar should be able to add or remove options
4. some hotkeys sound great

### Other projects

1. screenshot, especially gif
2. add a slogan on the desktop

## License

[MIT](https://github.com/RichardLitt/standard-readme/blob/master/LICENSE) © insorker

