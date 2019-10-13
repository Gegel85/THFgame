import javax.swing.JFileChooser;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JOptionPane;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
import javax.swing.JDialog;
import java.awt.HeadlessException;
import java.awt.Component;
import java.io.StringWriter;
import java.io.FileReader;
import java.io.FileInputStream;
import java.util.NavigableMap;
import java.util.TreeMap;

Map map;
JSONObject json;
String gamePath;
NavigableMap<String, PImage> sprites = new TreeMap<String, PImage>();

void error(String err)
{
        JOptionPane.showMessageDialog(null, err, "Error" , JOptionPane.ERROR_MESSAGE);
}

void draw()
{
        background(0);
        map.render();
}
