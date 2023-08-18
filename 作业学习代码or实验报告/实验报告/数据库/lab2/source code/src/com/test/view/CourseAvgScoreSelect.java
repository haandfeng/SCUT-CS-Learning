package com.test.view;


import com.test.dao.*;
import com.test.pojo.CourseAvgScore;
import com.test.pojo.StuAvgScore;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class CourseAvgScoreSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,selectPane;



	private JTextField txtCno,txtCname;

	private JLabel labCno, labCname;

	private JButton btnSelect;



	private JTable table;

	private JScrollPane scrollPane;



	private CourseAvgScoreDao couAvgScoreDao ;
	static String[] colSno= {"CID","Name","AvgScore"};


	public CourseAvgScoreSelect(){
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

		Object[][] r1=getSelect(couAvgScoreDao.selectCourseAvgScore(null));

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		selectPane=new JPanel(new GridLayout(2,2));



		labCno=new JLabel("CID");
		labCname=new JLabel("Name");


		txtCno=new JTextField(15);
		txtCname=new JTextField(15);



		selectPane.add(labCno);
		selectPane.add(txtCno);
		selectPane.add(labCname);
		selectPane.add(txtCname);



		centerPanel.add(selectPane);
		centerPanel.add(selectResultPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {


		couAvgScoreDao = new CourseAvgScoreDao();
	}

	public static Component getItemCom(){
		new CourseAvgScoreSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnSelect){

			String sno=txtCno.getText().trim();
			String sname=txtCname.getText().trim();



			CourseAvgScore sc = new CourseAvgScore();
			sc.setCno(sno);
			sc.setCname(sname);





			List<CourseAvgScore> scList = couAvgScoreDao.selectCourseAvgScore(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<CourseAvgScore> list){


		Object[][] results=new Object[list.size()][colSno.length];

		for(int i=0;i<list.size();i++){
			CourseAvgScore sc=list.get(i);
			results[i][0]=sc.getCno();
			results[i][1]=sc.getCname();
			results[i][2]=sc.getAvgScore();


		}

		return results;
	}


}
