package com.test.view;


import com.test.dao.TeacherDao;
import com.test.dao.UserDao;
import com.test.pojo.Teacher;
import com.test.pojo.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class UserUpdatePwd extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,teaPane;



	private JTextField txtOldPwd,txtNewPwd,txtConfirmPwd;

	private JLabel labOldPwd,labNewPwd,labConfirmPwd;

	private JButton btnAdd,btnReset;

	private static User user;

	private UserDao userDao ;



	public UserUpdatePwd(User u){
		setLayout(null);
		initService( u);
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);




		centerPanel=new JPanel();



		teaPane=new JPanel(new GridLayout(3,4));

		labOldPwd=new JLabel("Old password");
		labNewPwd=new JLabel("New password");
		labConfirmPwd=new JLabel("Confirm");


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

	private void initService(User u) {

		userDao = new UserDao();

		user = u;
	}

	public static Component getItemCom(User u){
		new UserUpdatePwd(u);
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

			User us = userDao.selectUserByName(UserUpdatePwd.user.getName());
			if (!us.getPassword().equals(oldPwd)){
				JOptionPane.showMessageDialog(null, "Old password not correct");
				return;
			}
			int i=userDao.updatePwd(us.getName(),newPwd);

			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				txtOldPwd.setText("");
				txtNewPwd.setText("");
				txtConfirmPwd.setText("");
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}

	}



}
