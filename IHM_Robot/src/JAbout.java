
	import java.awt.event.ActionEvent;
	import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
	import javax.swing.JFrame;
	import javax.swing.JLabel;
	import javax.swing.JPanel;

/**
 * 
 * @author Rodolphe LATOUR
 *
 *This class is aimed to give information to users. It's composed of only two elements : a text and a button.
 *The button, once pressed, will close the current window and open the main page of the software. 
 *
 */


	public class JAbout extends JFrame implements ActionListener {

		  public Main_page MP;
		  
		  private JPanel pan = new JPanel();
		  private JLabel lab1;
		  private JButton bt1 = new JButton("<HTML><font face=\"Times\">Back</font></HTML>");
		  

		  public JAbout() {    			    
				lab1 = new JLabel();
				lab1.setText(lab1.getText() + "<HTML><BODY><font face=\"courier\">This software has been created in order to control a robot based"
						+ "<BR> on a MSP430 microprocessor. "
						+ "You can connect the software to a <BR>bluetooth equipped device and "
						+ "move the robot by clicking on the<BR> appropriate button."
						+ "<BR><BR>To connect the software to your robot, click on file and connect."
						+ "<BR>Choose your device on the list and click on \"Valid\". "
						+ "You'll be <BR>connected to your robot.</font></BODY></HTML>");
				this.setTitle("About the software");
				this.setIconImage(new ImageIcon(this.getClass().getResource("robot.png")).getImage());
			    this.setSize(480, 250);
			    this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
			    this.setLocationRelativeTo(null);
			    this.setContentPane(pan);
			    pan.setLayout(null);
			    
			    pan.add(bt1);
				bt1.addActionListener(this);
			    bt1.setBounds(360, 170, 80, 30);
		    
			    pan.add(lab1);
			    lab1.setBounds(10, 10, 500, 150);

			    
			    this.setResizable(false);

		  }

		  
			public void actionPerformed(ActionEvent e) {
				if(e.getSource()==bt1){
					this.dispose();
				}		
	}
}

