package com.test.view;


import com.test.dao.*;
import com.test.pojo.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class StuAvgScoreSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,selectPane,scPane;



	private JTextField txtSno,txtSname,txtAvgScore;

	private JLabel labSno, labSname,labAvgScore;

	private JButton btnSelect;



	private JTable table;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	private StudentDao studentDao ;
	private TeacherDao teacherDao ;
	private ScDao scDao ;
	private StudentGradeDao gradeDao ;
	private StudentAvgScoreDao studentAvgScoreDao ;
	private StuAvgScoreDao stuAvgScoreDao ;
	static String[] colSno= {"ID","Name","AvgScore"};


	public StuAvgScoreSelect(){
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

		Object[][] r1=getSelect(studentAvgScoreDao.selectStudentAvgScore(null));

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		selectPane=new JPanel(new GridLayout(2,2));


	
		labSno=new JLabel("ID");
		labSname=new JLabel("NAme");


		txtSno=new JTextField(15);
		txtSname=new JTextField(15);



		selectPane.add(labSno);
		selectPane.add(txtSno);
		selectPane.add(labSname);
		selectPane.add(txtSname);


		scPane = new JPanel();

		scPane=new JPanel(new GridLayout(1,2));
		labAvgScore=new JLabel("All student average score");
		txtAvgScore=new JTextField(15);
		txtAvgScore.setEditable(false);

		scPane.add(labAvgScore);
		scPane.add(txtAvgScore);

		StuAvgScore avgScore = stuAvgScoreDao.selectAvgScore();
		txtAvgScore.setText(avgScore.getAvgScore() + "");

		centerPanel.add(selectPane);
		centerPanel.add(selectResultPane);
		centerPanel.add(scPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		courseDao = new CourseDao();
		studentDao = new StudentDao();
		teacherDao = new TeacherDao();
		scDao = new ScDao();
		gradeDao = new StudentGradeDao();
		studentAvgScoreDao = new StudentAvgScoreDao();
		stuAvgScoreDao = new StuAvgScoreDao();
	}

	public static Component getItemCom(){
		new StuAvgScoreSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnSelect){

			String sno=txtSno.getText().trim();
			String sname=txtSname.getText().trim();



			StuAvgScore sc = new StuAvgScore();
			sc.setSno(sno);
			sc.setSname(sname);





			List<StuAvgScore> scList =  studentAvgScoreDao.selectStudentAvgScore(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<StuAvgScore> list){


		Object[][] results=new Object[list.size()][colSno.length];

		for(int i=0;i<list.size();i++){
			StuAvgScore sc=list.get(i);
			results[i][0]=sc.getSno();
			results[i][1]=sc.getSname();
			results[i][2]=sc.getAvgScore();


		}

		return results;
	}


}
