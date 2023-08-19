package com.test.view;


import com.test.dao.CourseDao;
import com.test.pojo.Course;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class CourseSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,coursePane;



	private JTextField txtcno,txtName,txtTno;

	private JLabel labCno,labName,labTno;

	private JButton btnSelect;


	private JTable table;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	static String[] colName= {"CID","Course Name","Instructor ID","Instructor Name","Credit","Grade","Cancel year"};


	public CourseSelect(){
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

		Object[][] r1=getSelect(courseDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		coursePane=new JPanel(new GridLayout(7,4));

		labCno=new JLabel("CID");
		labName=new JLabel("Course Name");
		labTno=new JLabel("Instructor ID");

		txtcno=new JTextField(15);

		txtName=new JTextField(15);


		txtTno=new JTextField(15);


		coursePane.add(labCno);
		coursePane.add(txtcno);
		coursePane.add(labName);		
		coursePane.add(txtName);
		coursePane.add(labTno);
		coursePane.add(txtTno);



		centerPanel.add(coursePane);
		centerPanel.add(selectResultPane);


		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		courseDao = new CourseDao();
	}

	public static Component getItemCom(){
		new CourseSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){


		if(e.getSource()==btnSelect){

			Course course=new Course();
			course.setCno(txtcno.getText().trim());

			course.setCname(txtName.getText().trim());

			course.setTno(txtTno.getText().trim());




			List<Course> courses =  courseDao.select(course);
			
			Object[][] r1=getSelect(courses);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);

		}
	}

	Object[][] getSelect(List<Course> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Course course=list.get(i);
			results[i][0]=course.getCno();
			results[i][1]=course.getCname();
			results[i][2]=course.getTno();
			results[i][3]=course.getTname();
			results[i][4]=course.getCredit();
			results[i][5]=course.getFaceYear();
			if (course.getCanceledYear() != null){
				results[i][6]=course.getCanceledYear();
			}

		}

		return results;
	}


}
