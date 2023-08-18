package com.test.view;


import com.test.dao.CourseDao;
import com.test.dao.ScDao;
import com.test.dao.StudentDao;
import com.test.dao.TeacherDao;
import com.test.pojo.Course;
import com.test.pojo.Sc;
import com.test.pojo.Student;
import com.test.pojo.Teacher;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ScSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,scPane;



	private JTextField txtCno, txtTno,txtYear;

	private JLabel labCno,labTno, labYear;

	private JButton btnSelect;


	private JTable table;

	private static Student s;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	private StudentDao studentDao ;
	private TeacherDao teacherDao ;
	private ScDao scDao ;
	static String[] colSno= {"课程号","教师编号","年份","成绩"};


	public ScSelect(Student student){
		setLayout(null);
		initService(student);
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnSelect=new JButton("查询");

		btnSelect.addActionListener(this);



		btnPanel.add(btnSelect);
		panel.add(btnPanel,BorderLayout.NORTH);

		centerPanel=new JPanel();
		selectResultPane=new JPanel();


		table=new JTable();
		scrollPane=new JScrollPane(table);

		Sc sc = new Sc();
		sc.setSno(s.getSno());
		Object[][] r1=getSelect(scDao.select(sc));

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		scPane=new JPanel(new GridLayout(5,4));


		labCno=new JLabel("课程号");

		labTno=new JLabel("教师编号");
		labYear=new JLabel("年份");

		txtCno=new JTextField(15);


		txtTno=new JTextField(15);

		
		txtYear=new JTextField(15);

		scPane.add(labCno);
		scPane.add(txtCno);
		scPane.add(labTno);
		scPane.add(txtTno);
		scPane.add(labYear);		
		scPane.add(txtYear);




		centerPanel.add(scPane);
		centerPanel.add(selectResultPane);


		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService(Student student) {

		courseDao = new CourseDao();
		studentDao = new StudentDao();
		teacherDao = new TeacherDao();
		scDao = new ScDao();

		s = student;

	}

	public static Component getItemCom(Student stu){
		new ScSelect( stu);
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){


		if(e.getSource()==btnSelect){


		
			String cno=txtCno.getText().trim();

			String tno=txtTno.getText().trim();




			Sc sc = new Sc();
			sc.setSno(s.getSno());
			sc.setCno(cno);
			sc.setTno(tno);




			List<Sc> scList =  scDao.select(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<Sc> list){


		Object[][] results=new Object[list.size()][colSno.length];

		for(int i=0;i<list.size();i++){
			Sc sc=list.get(i);
			results[i][0]=sc.getCno();
			results[i][1]=sc.getTno();
			results[i][2]=sc.getYear();
			if (sc.getScore() != null){
				results[i][3]=sc.getScore();
			}

		}

		return results;
	}


}
