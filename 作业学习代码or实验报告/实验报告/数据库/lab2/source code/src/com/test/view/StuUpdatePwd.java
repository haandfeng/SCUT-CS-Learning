package com.test.view;


import com.test.dao.StudentDao;
import com.test.pojo.Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StuUpdatePwd extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,teaPane;



	private JTextField txtOldPwd,txtNewPwd,txtConfirmPwd;

	private JLabel labOldPwd,labNewPwd,labConfirmPwd;

	private JButton btnAdd,btnReset;

	private static Student user;

	private StudentDao userDao ;



	public StuUpdatePwd(Student u){
		setLayout(null);
		initService( u);
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);




		centerPanel=new JPanel();



		teaPane=new JPanel(new GridLayout(3,4));

		labOldPwd=new JLabel("Old password");
		labNewPwd=new JLabel("New password");
		labConfirmPwd=new JLabel("Confirm password");


		txtOldPwd=new JTextField(15);

		txtNewPwd=new JTextField(15);
		txtConfirmPwd=new JTextField(15);





		teaPane.add(labOldPwd);
		teaPane.add(txtOldPwd);
		teaPane.add(labNewPwd);
		teaPane.add(txtNewPwd);
		teaPane.add(labConfirmPwd);
		teaPane.add(txtConfirmPwd);


		centerPanel.add(teaPane);



		panel.add(centerPanel,BorderLayout.CENTER);

		btnPanel=new JPanel();
		btnAdd=new JButton("Modify");
		btnReset=new JButton("Reset");

		btnReset.addActionListener(this);
		btnAdd.addActionListener(this);


		btnPanel.add(btnAdd);
		btnPanel.add(btnReset);

		panel.add(btnPanel,BorderLayout.SOUTH);


	}

	private void initService(Student u) {

		userDao = new StudentDao();

		user = u;
	}

	public static Component getItemCom(Student u){
		new StuUpdatePwd(u);
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnReset){
			txtOldPwd.setText("");
			txtNewPwd.setText("");
			txtConfirmPwd.setText("");

		}



		if(e.getSource()==btnAdd){
			String oldPwd=txtOldPwd.getText().trim();
			String newPwd=txtNewPwd.getText().trim();
			String confirmPwd=txtConfirmPwd.getText().trim();

			if (!newPwd.equals(confirmPwd)){
				JOptionPane.showMessageDialog(null, "Password not consistency");
				return;
			}

			Student us = userDao.selectBySno(StuUpdatePwd.user.getSno());
			if (!us.getPassword().equals(oldPwd)){
				JOptionPane.showMessageDialog(null, "Old password not correct");
				return;
			}
			int i=userDao.updatePwd(us.getSno(),newPwd);

			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				txtOldPwd.setText("");
				txtNewPwd.setText("");
				txtConfirmPwd.setText("");
			}else {
				JOptionPane.showMessageDialog(null, "Operation Fail");
			}


		}

	}



}
