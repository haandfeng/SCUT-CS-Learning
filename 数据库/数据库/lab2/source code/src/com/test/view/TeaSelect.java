package com.test.view;


import com.test.dao.TeacherDao;
import com.test.pojo.Teacher;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class TeaSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,teaPane;



	private JTextField txttno,txtName;

	private JLabel labTno,labName;

	private JButton btnSelect;



	private JTable table;

	private JScrollPane scrollPane;

	private TeacherDao teaDao ;
	static String[] colName= {"Instructor ID","Instructor Name","Teaching Course"};


	public TeaSelect(){
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

		Object[][] r1=getSelect(teaDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		teaPane=new JPanel(new GridLayout(5,4));

		labTno=new JLabel("Instructor ID");
		labName=new JLabel("Name");


		txttno=new JTextField(15);

		txtName=new JTextField(15);




		teaPane.add(labTno);
		teaPane.add(txttno);
		teaPane.add(labName);		
		teaPane.add(txtName);


		centerPanel.add(teaPane);
		centerPanel.add(selectResultPane);




		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		teaDao = new TeacherDao();
	}

	public static Component getItemCom(){
		new TeaSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnSelect){

			Teacher tea=new Teacher();
			tea.setTno(txttno.getText().trim());



			tea.setTname(txtName.getText().trim());



			List<Teacher> teas =  teaDao.select(tea);
			
			Object[][] r1=getSelect(teas);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<Teacher> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Teacher tea=list.get(i);
			results[i][0]=tea.getTno();
			results[i][1]=tea.getTname();
			results[i][2]=tea.getCourses();
		}

		return results;
	}


}
