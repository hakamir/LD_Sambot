import java.awt.Color;
import java.awt.Component;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * 
 * @author Rodolphe LATOUR
 *
 *
 *This is the main page of the software. It's composed of multiple button which interact with a MSP430's based robot.
 *The four arrows and the cube permit to users to move the robot in the intended direction. 
 *An indicator to left inform of which device is piloted. 
 *To choose the needed device, go to the "File" dropdown menu and click on "Connect". It leads to an new JConnect window.
 *Users can got help by clicking on "About the software" in "Help" dropdown menu. 
 *
 *
 *The robot can receive 7 different characters to operate :
 *
 *		¤ It stop when the character "S" is echoed (echo performed by clicking on the red square).
 *		¤ It go forward when the character "F" is echoed (echo performed by clicking on the up arrow).
 *		¤ It go backward when the character "B" is echoed (echo performed by clicking on the down arrow).
 *		¤ It turn left when the character "L" is echoed (echo performed by clicking on the left arrow).
 *		¤ It turn right when the character "R" is echoed (echo performed by clicking on the right arrow).
 *		¤ It set the connection by clicking on the "Connect" button.
 *		¤ It stop and disconnect by clicking on the "Disconnect" button.
 *
 *When users quit the software, the connection between the computer and the robot is disabled.
 *
 */

public class Main_page extends JFrame implements ActionListener {
	
	/** We initialize the JC and JA windows but both won't be shown before clicking on the appropriate button **/
	  public JConnect JC = new JConnect();
	  public JAbout JA = new JAbout();
	  
	  private JPanel pan = new JPanel();
	  private JLabel lab1;
	  private JLabel lab2;
	  public static JLabel device;
	  private JButton shd = new JButton("Disconnect");
	  private JButton ini = new JButton("Connect");
	  private JButton fw = new JButton("Forward");
	  private JButton bw = new JButton("Backward");
	  private JButton rgt = new JButton("Right");
	  private JButton lft = new JButton("Left");
	  private JButton stp = new JButton("STOP");
	  private JMenuBar menu = new JMenuBar();
	  private JMenu file = new JMenu("File");
	  private JMenu help = new JMenu("Help");
	  private JMenuItem connect = new JMenuItem("Connect");
	  private JMenuItem quit = new JMenuItem("Quit");
	  private JMenuItem about = new JMenuItem("About the software");
	  

	  public Main_page() {
		    JA.dispose();
		    JC.dispose();
			lab1 = new JLabel("Device : ");
			lab2 = new JLabel("N/A");
			device = new JLabel("<html><font color='red'>N/A</font></html>");
			this.setTitle("Robot Control Software");
			this.setIconImage(new ImageIcon(this.getClass().getResource("robot.png")).getImage()); 
		    this.setSize(366, 500);    
		    
		    /**
		     * Start
		     * -----------------------------------------------------------------------------
		     * This function below opens a dialog box when the user clicks on the close cross.
		     * If you choose yes, the application closes.
		     * Otherwise the application stays open.
		     * 
		     */
		    
		    this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);		//Clicking on the cross do nothing
		    this.addWindowListener(new WindowAdapter() {
		    	public void windowClosing(WindowEvent e) {
		    		Component frame = null;
					int n = JOptionPane.showConfirmDialog(
				    	    frame,
				    	    "Do you really want to quit?",					//Message in the dialog box
				    	    "Confirm closure",								//Name of the dialog box
				    	    JOptionPane.YES_NO_OPTION);						//Type of options
					if(n == JOptionPane.YES_OPTION)							//Condition if YES is chosen
					{
						dispose();											//Close
					}
		    	}
		    });
		    
		    /**
		     * -------------------------------------------------------------------------------
		     * End
		     */
		    
		    this.setLocationRelativeTo(null);
		    this.setContentPane(pan);
		    pan.setLayout(null);
		    
		    pan.add(menu);
		    menu.setBounds(0, 0, 360, 30);
		    menu.add(file);
		    menu.add(help);
		    file.add(connect);
		    connect.addActionListener(this);
		    file.add(quit);
		    quit.addActionListener(this);
		    help.add(about);
		    about.addActionListener(this);
		    

		    pan.add(shd);
			shd.addActionListener(this);
		    shd.setBounds(250, 380, 100, 30);
		    
		    
		    pan.add(ini);
			ini.addActionListener(this);
		    ini.setBounds(250, 340, 100, 30);
		    
		    
		    /**
		     * Start
		     * -----------------------------------------------------------------------------
		     * This function below puts a button with an image only
		     * 
		     */
		    
		    pan.add(fw);
			fw.addActionListener(this);
		    fw.setBounds(130, 80, 100, 100); 
		    try {
		        Image img1 = ImageIO.read(getClass().getResource("arrow_u.png"));
		        fw.setIcon(new ImageIcon(img1));
		      } catch (Exception ex) {
		        System.out.println(ex);
		      }
		    fw.setBackground(Color.GRAY);
		    fw.setOpaque(false);
		    fw.setBorder(null);
		    
		    /**
		     * -------------------------------------------------------------------------------
		     * End
		     */
		    
		    pan.add(bw);
			bw.addActionListener(this);
		    bw.setBounds(130, 320, 100, 100);
		    try {
		        Image img2 = ImageIO.read(getClass().getResource("arrow_d.png"));
		        bw.setIcon(new ImageIcon(img2));
		      } catch (Exception ex) {
		        System.out.println(ex);
		      }
		    bw.setBackground(Color.GRAY);
		    bw.setOpaque(false);
		    bw.setBorder(null);
		    
		    pan.add(rgt);
			rgt.addActionListener(this);
		    rgt.setBounds(250, 200, 100, 100);
		    try {
		        Image img3 = ImageIO.read(getClass().getResource("arrow_r.png"));
		        rgt.setIcon(new ImageIcon(img3));
		      } catch (Exception ex) {
		        System.out.println(ex);
		      }
		    rgt.setBackground(Color.GRAY);
		    rgt.setOpaque(false);
		    rgt.setBorder(null);
		    
		    pan.add(lft);
			lft.addActionListener(this);
		    lft.setBounds(10, 200, 100, 100);
		    try {
		        Image img4 = ImageIO.read(getClass().getResource("arrow_l.png"));
		        lft.setIcon(new ImageIcon(img4));
		      } catch (Exception ex) {
		        System.out.println(ex);
		      }
		    lft.setBackground(Color.GRAY);
		    lft.setOpaque(false);
		    lft.setBorder(null);
		    
		    pan.add(stp);
			stp.addActionListener(this);
		    stp.setBounds(130, 200, 100, 100);
		    try {
		        Image img5 = ImageIO.read(getClass().getResource("red_square.png"));
		        stp.setIcon(new ImageIcon(img5));
		      } catch (Exception ex) {
		        System.out.println(ex);
		      }
		    stp.setBackground(Color.GRAY);
		    stp.setOpaque(false);
		    stp.setBorder(null);
		    
		    pan.add(lab1);
		    lab1.setBounds(30, 40, 300, 30);
		    
		    
		    pan.add(lab2);
		    lab2.setBounds(280, 40, 300, 30);
		    
		    
		    pan.add(device);
			//JConnect.listModel.getListeners(DeviceListener);
		    device.setBounds(100, 40, 80, 30);
		    
			stp.setEnabled(false);
		    this.setVisible(true);
		    this.setResizable(false);

	  }
	  

	  public void actionPerformed(ActionEvent e) {
			if(e.getSource()==fw){
				 lab2.setText("Forward");
				 fw.setEnabled(false);
				 bw.setEnabled(true);
				 rgt.setEnabled(true);
				 lft.setEnabled(true);
				 stp.setEnabled(true);
				 //TODO Send "F" to device
			}
			if(e.getSource()==bw){
				 lab2.setText("Backward");
				 fw.setEnabled(true);
				 bw.setEnabled(false);
				 rgt.setEnabled(true);
				 lft.setEnabled(true);
				 stp.setEnabled(true);
				 //TODO Send "B" to device
			}
			if(e.getSource()==rgt){
				 lab2.setText("Right");
				 fw.setEnabled(true);
				 bw.setEnabled(true);
				 rgt.setEnabled(false);
				 lft.setEnabled(true);
				 stp.setEnabled(true);
				 //TODO Send "R" to device
			}
			if(e.getSource()==lft){
				 lab2.setText("Left");
				 fw.setEnabled(true);
				 bw.setEnabled(true);
				 rgt.setEnabled(true);
				 lft.setEnabled(false);
				 stp.setEnabled(true);
				 //TODO Send "L" to device
			}
			if(e.getSource()==stp){
				 lab2.setText("Stop");
				 fw.setEnabled(true);
				 bw.setEnabled(true);
				 rgt.setEnabled(true);
				 lft.setEnabled(true);
				 stp.setEnabled(false);
				 //TODO Send "S" to device
			}
			if(e.getSource()==connect){
			    JC.setVisible(true);
				if (JC.isVisible()==false)
				{
					JC = new JConnect();
				}	
			}
			if(e.getSource()==shd){
				 lab2.setText("N/A");
				 fw.setEnabled(true);
				 bw.setEnabled(true);
				 rgt.setEnabled(true);
				 lft.setEnabled(true);
				 stp.setEnabled(false);
				 device.setText("<html><font color='red'>N/A</font></html>");
				 //TODO Shutdown connection to device
			}
			if(e.getSource()==ini){
				//TODO Set connection to the selected device
			}
			if(e.getSource()==quit){
				this.dispose();
			}
			/** The window won't open if it already is **/
			if(e.getSource()==about){
				JA.setVisible(true);
				if (JA.isVisible()==false)
				{
					JA = new JAbout();
				}							
			}
	  }
}