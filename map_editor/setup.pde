class MyFilter extends FileFilter
{
        private String _fileName;
        
        MyFilter(String fileName)
        {
                this._fileName = fileName;
        }
        
        boolean accept(File f)
        {
                return f.isDirectory() || f.getName().compareTo(this._fileName) == 0;
        }
        
        String getDescription()
        {
                return this._fileName;
        }
}

String askPath(String basePath, String title, FileFilter filter)
{
        JFileChooser fileChooser = new JFileChooser(new File(basePath)) {
            @Override
            protected JDialog createDialog(Component parent) throws HeadlessException {
                JDialog dialog = super.createDialog(parent);

                dialog.setIconImage(new ImageIcon(gamePath + "/assets/" + json.getString("icon")).getImage());
                return dialog;
            }
        };
        
        fileChooser.setFileFilter(filter);
        fileChooser.setDialogTitle(title);

        int response = fileChooser.showOpenDialog(null);
        
        if (response == JFileChooser.APPROVE_OPTION)
                return fileChooser.getSelectedFile().getAbsolutePath();
        else
                return null;
}

String getGamePath()
{
        String path = ".";

        try {
                FileReader fileReader = new FileReader(new File("lastPath.txt"));
                BufferedReader bufferedReader = new BufferedReader(fileReader);
                
                path = bufferedReader.readLine();
                bufferedReader.close();
                fileReader.close();
        } catch (Exception e) {}

        JFileChooser fileChooser = new JFileChooser(path);
        FileFilter filter = new MyFilter("list.json");
        
        fileChooser.setDialogTitle("Locate game assets");
        fileChooser.setFileFilter(filter);

        int response = fileChooser.showOpenDialog(null);
        
        if (response == JFileChooser.APPROVE_OPTION) {
                try {
                        json = loadJSONObject(fileChooser.getSelectedFile().getAbsolutePath());

                        PrintWriter output = new PrintWriter("lastPath.txt");

                        output.println(fileChooser.getSelectedFile().getParentFile().getAbsolutePath());
                        output.flush();
                        output.close();
                } catch (Exception e) {
                        StringWriter writer = new StringWriter();
                        PrintWriter printWriter = new PrintWriter( writer );

                        e.printStackTrace(printWriter);
                        printWriter.flush();
                        
                        error(writer.toString());
                }
                path = fileChooser.getSelectedFile().getParentFile().getParentFile().getAbsolutePath();
        } else {
                println("Canceled...");
                System.exit(0);
        }
        return path;
}

void loadSprites(JSONObject paths)
{
        Object[] keys = paths.keys().toArray();

        for (int i = 0; i < keys.length; i++)
                sprites.put(keys[i].toString(), loadImage(gamePath + "/assets/" + paths.get(keys[i].toString())));
}

void setup()
{
        surface.setSize(640, 480);
        surface.setVisible(false);
        surface.setFrameRate(60);
        surface.setTitle("THFGame map editor");
        surface.setResizable(true);
        
        gamePath = getGamePath();

        PImage icon = loadImage(gamePath + "/assets/" + json.getString("icon"));

        loadSprites(json.getJSONObject("sprites"));
        if (icon != null)
                surface.setIcon(icon);
                
        String path = askPath(gamePath + "/assets/maps", "Open map file", new FileNameExtensionFilter("THFGame map file", "map"));

        try {
                map = new Map(path);
        } catch (Exception e) {
                StringWriter writer = new StringWriter();
                PrintWriter printWriter = new PrintWriter(writer);

                e.printStackTrace(printWriter);
                printWriter.flush();

                error("Cannot load file " + path + ":\n" + writer.toString());
       
                exit();
        }

        surface.setVisible(true);
}
