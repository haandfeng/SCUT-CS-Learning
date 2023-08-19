package com.test.view;


import com.test.dao.StudentDao;
import com.test.pojo.Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class StuSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,stuPane;



	private JTextField txtsno,txtName;

	private JLabel labSno,labName;

	private JButton btnSelect;



	private JTable table;

	private JScrollPane scrollPane;

	private StudentDao stuDao ;
	static String[] colName= {"ID","Name","Sex","Age","Year","Grade"};


	public StuSelect(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();

		btnSelect=new JButton("Search");

		btnSelect.addActionListener(this);




		btnPanel.add(btnSelect);

		panel.add(btnPanel,BorderLayout.NORTH);

		centerPanel=new JPanel();
		selectResultPane=new JPanel();


		table=new JTable();
		scrollPane=new JScrollPane(table);

		Object[][] r1=getSelect(stuDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		stuPane=new JPanel(new GridLayout(3,2));

		labSno=new JLabel("ID");
		labName=new JLabel("Name");


		txtsno=new JTextField(15);

		txtName=new JTextField(15);




		stuPane.add(labSno);
		stuPane.add(txtsno);
		stuPane.add(labName);		
		stuPane.add(txtName);




		centerPanel.add(stuPane);
		centerPanel.add(selectResultPane);


		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		stuDao = new StudentDao();
	}

	public static Component getItemCom(){
		new StuSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){


		if(e.getSource()==btnSelect){

			Student stu=new Student();
			stu.setSno(txtsno.getText().trim());



			stu.setSname(txtName.getText().trim());



			List<Student> stus =  stuDao.select(stu);
			
			Object[][] r1=getSelect(stus);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<Student> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Student stu=list.get(i);
			results[i][0]=stu.getSno();
			results[i][1]=stu.getSname();
			results[i][2]=stu.getSsex();
			results[i][3]=stu.getEntranceAge();
			results[i][4]=stu.getEntranceYear();
			results[i][5]=stu.getClazz();
		}

		return results;
	}


}
