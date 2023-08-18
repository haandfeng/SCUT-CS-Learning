package com.test.view;


import com.test.dao.StudentDao;
import com.test.pojo.Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StuMsg extends JFrame   {
	private static JPanel  panel,btnPanel, centerPanel,stuPane;


	private JTextField txtsno,txtName, txtEntrancAge,txtEntrancYear,txtClazz,txtSex;

	private JLabel labSno,labName,labSex, labEntrancAge,labEntrancYear,labClazz;


	private static Student user;

	private StudentDao userDao ;



	public StuMsg(Student u){
		setLayout(null);
		initService( u);
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);




		centerPanel=new JPanel();



		stuPane=new JPanel(new GridLayout(6,4));
		labSno=new JLabel("ID");
		labName=new JLabel("Name");
		labSex=new JLabel("Sex");
		labEntrancAge=new JLabel("Age");
		labEntrancYear=new JLabel("Grade");
		labClazz=new JLabel("Class");

		txtsno=new JTextField(15);

		txtName=new JTextField(15);


		txtEntrancAge=new JTextField(15);
		txtSex=new JTextField(15);

		txtEntrancYear=new JTextField(15);
		txtClazz=new JTextField(15);

		txtsno.setEditable(false);
		txtName.setEditable(false);
		txtEntrancAge.setEditable(false);
		txtEntrancYear.setEditable(false);
		txtClazz.setEditable(false);
		txtSex.setEditable(false);

		Student student = userDao.selectBySno(u.getSno());
		txtsno.setText(student.getSno());
		txtName.setText(student.getSname());
		txtEntrancAge.setText(student.getEntranceAge() +"");
		txtEntrancYear.setText(student.getEntranceYear() +"");
		txtClazz.setText(student.getClazz());
		txtSex.setText(student.getSsex());


		stuPane.add(labSno);
		stuPane.add(txtsno);
		stuPane.add(labName);
		stuPane.add(txtName);
		stuPane.add(labSex);
		stuPane.add(txtSex);
		stuPane.add(labEntrancAge);
		stuPane.add(txtEntrancAge);
		stuPane.add(labEntrancYear);
		stuPane.add(txtEntrancYear);
		stuPane.add(labClazz);
		stuPane.add(txtClazz);


		centerPanel.add(stuPane);



		panel.add(centerPanel,BorderLayout.CENTER);

		btnPanel=new JPanel();



		panel.add(btnPanel,BorderLayout.SOUTH);


	}

	private void initService(Student u) {

		userDao = new StudentDao();

		user = u;
	}

	public static Component getItemCom(Student u){
		new StuMsg(u);
		return panel;

	}





}
