import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * 
 * 
 * @author Rodolphe LATOUR
 *
 *This window shows the devices detected by the computer with the bluetooth connection. 
 *We can click on the desired device to select it. 
 *Once the device select, we can either click of back to cancel the action and go back to the previous window,
 *or we can click on valid and the connection between the device and the application will perform. 
 *An authentication must be needed to ensure the connection to a MSP430's robot only. 
 *Other devices must not interact with the software.
 *
 *The list of devices refresh automatically to show new apertures as quick as possible. 
 *
 *
 */


public class JConnect extends JFrame implements ListSelectionListener, ActionListener {

	  public Main_page MP;
	  public static DefaultListModel listModel;
	  public JList list;
	  
	  
	  private JPanel pan = new JPanel();
	  private JLabel lab1;
	  private JButton bt1 = new JButton("Back");
	  private JButton bt2 = new JButton("Valid");



	  public JConnect() {
        	listModel = new DefaultListModel();
        	for(int i=0; i<=30;i++)
        	{
        		listModel.addElement("MSP430_"+i);
        	}

        	
		    list = new JList(listModel);
		    
			lab1 = new JLabel("Choose your device among the list:");
			
			this.setTitle("Set connection to a device");
			this.setIconImage(new ImageIcon(this.getClass().getResource("robot.png")).getImage());
		    this.setSize(320, 460);
		    this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		    this.setLocationRelativeTo(null);
		    this.setContentPane(pan);
		    pan.setLayout(null);
		    
		    pan.add(bt1);
			bt1.addActionListener(this);
		    bt1.setBounds(180, 380, 80, 30);
		    
		    pan.add(bt2);
			bt2.addActionListener(this);
		    bt2.setBounds(80, 380, 80, 30);
		    
		    
		    pan.add(lab1);
		    lab1.setBounds(10, 00, 300, 30);

		    list.setLayoutOrientation(JList.VERTICAL);
		    list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		    list.setSelectedIndex(0);
        	list.addListSelectionListener(this);
        	list.setVisibleRowCount(5);
        	
        	JScrollPane listScrollPane = new JScrollPane(list);
        	pan.add(listScrollPane, BorderLayout.CENTER);
        	listScrollPane.setVisible(true);
        	listScrollPane.setBounds(10, 30, 290, 300);

        	
        	
		    this.setResizable(false);

	  }

	  
		public void actionPerformed(ActionEvent e) {
			if(e.getSource()==bt1){
				Main_page.device.setText("<html><font color='red'>N/A</font></html>");
				this.dispose();
			}
			
			if(e.getSource()==bt2){
				this.dispose();		
			}
	
		
}


		public void valueChanged(ListSelectionEvent arg0) {
			Main_page.device.setText("" + list.getSelectedValue()); //Set value of the device on the main page  
			
		}
}
