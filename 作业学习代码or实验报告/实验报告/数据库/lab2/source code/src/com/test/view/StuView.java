package com.test.view;

import com.test.pojo.Student;
import com.test.pojo.User;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StuView extends JFrame {

	private JPanel contentPane;
	CardLayout cardLayout=new CardLayout();

	Dimension frameSize = new Dimension(900, 600);

	/**
	 * Launch the application.
	 */
	/**
	 * Create the frame.
	 */
	public StuView(Student user) {
		setTitle("MIS(Student)");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//setBounds(100, 100, 900, 600);
		setSize(frameSize);
		setLocationRelativeTo(null);

		contentPane = new JPanel();
		contentPane.setBorder(new TitledBorder(null, "Main", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBorder(new TitledBorder(new EtchedBorder(EtchedBorder.LOWERED, new Color(255, 255, 255), new Color(160, 160, 160)), "MIS", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel.setBounds(117, 10, 750, 500);
		contentPane.add(panel);
		panel.setLayout(cardLayout);
		
//		ÃÌº”√Ê∞Â


		panel.add(StuMsg.getItemCom(user),"stuView");
		panel.add(TeaSelect.getItemCom(),"teaView");
		panel.add(CourseSelect.getItemCom(),"courseView");
		panel.add(ScSelect.getItemCom(user),"scView");
		panel.add(StuUpdatePwd.getItemCom(user),"pwdView");


		

		
		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new TitledBorder(null, "Menu", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_1.setBounds(10, 34, 120, 400);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JButton btnNewButton = new JButton("Personal");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "stuView");
			}
		});
		btnNewButton.setBounds(0, 26, 97, 23);
		panel_1.add(btnNewButton);
		
		JButton btnNewButton_1 = new JButton("Teacher");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "teaView");
			}
		});
		btnNewButton_1.setBounds(0, 59, 97, 23);
		panel_1.add(btnNewButton_1);
		
		JButton btnNewButton_2 = new JButton("Course");
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "courseView");
			}
		});
		btnNewButton_2.setBounds(0, 92, 97, 23);
		panel_1.add(btnNewButton_2);
		
		JButton btnNewButton_2_1 = new JButton("SelectC ");
		btnNewButton_2_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "scView");
			}
		});
		btnNewButton_2_1.setBounds(0, 127, 97, 23);
		panel_1.add(btnNewButton_2_1);


		JButton btnNewButton_3 = new JButton("Password");
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "pwdView");
			}
		});
		btnNewButton_3.setBounds(0, 161, 97, 23);
		panel_1.add(btnNewButton_3);

		
		JButton btnNewButton_2_1_1 = new JButton("Exit");
		btnNewButton_2_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Login login=new Login();
				login.setVisible(true);
				dispose();
			}
		});
		btnNewButton_2_1_1.setBounds(0, 195, 97, 23);
		panel_1.add(btnNewButton_2_1_1);
	}

//	public static void main(String[] args) {
//		MainView main=new MainView();
//		main.setVisible(true);
//	}
}
