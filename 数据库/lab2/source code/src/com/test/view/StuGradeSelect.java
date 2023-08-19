package com.test.view;


import com.test.dao.StudentGradeDao;
import com.test.pojo.StudentGrade;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class StuGradeSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,stuGradePane,sqlPane;



	private JTextField txtsno,txtSname;

	private JLabel labSno,labSname;

	private JTextField txtcno,txtCname;

	private JLabel labCno,labCname;

	private JTextField txtTno,txtTname;

	private JLabel labTno,labTname;
	

	private JButton btnSelect;

	private JTextArea sqlArea;

	private JTable table;

	private JScrollPane scrollPane;

	private StudentGradeDao stuGradeDao ;
	static String[] colName= {"ID","Name","Sex","Age","Grade","Class",
			"CID","Course Name","Instructor ID","Instructor Name","Credit","Year","Score"};


	public StuGradeSelect(){
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

		Object[][] r1=getSelect(stuGradeDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(720,200));
		selectResultPane.add(scrollPane);


		stuGradePane=new JPanel(new GridLayout(6,4));

		labSno=new JLabel("ID");
		labSname=new JLabel("Name");

		txtsno=new JTextField(15);

		txtSname=new JTextField(15);




		stuGradePane.add(labSno);
		stuGradePane.add(txtsno);
		stuGradePane.add(labSname);		
		stuGradePane.add(txtSname);

		labCno=new JLabel("CID");
		labCname=new JLabel("Course Name");
		labTno=new JLabel("Instructor ID");
		labTname=new JLabel("Instructor Name");

		txtcno=new JTextField(15);

		txtCname=new JTextField(15);


		txtTno=new JTextField(15);

		txtTname=new JTextField(15);


		stuGradePane.add(labCno);
		stuGradePane.add(txtcno);
		stuGradePane.add(labCname);
		stuGradePane.add(txtCname);
		stuGradePane.add(labTno);
		stuGradePane.add(txtTno);
		stuGradePane.add(labTname);
		stuGradePane.add(txtTname);





		sqlPane = new JPanel();
		sqlArea = new JTextArea(4,60);
		sqlArea.setEditable(false);

		sqlArea.setLineWrap(true);        //激活自动换行功能
		sqlArea.setWrapStyleWord(true);
//		JScrollPane scroll = new JScrollPane(sqlArea);
//		scroll.setSize (600,200) ;

		sqlPane.add(sqlArea);

		centerPanel.add(stuGradePane);
		centerPanel.add(selectResultPane);
		centerPanel.add(sqlPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		stuGradeDao = new StudentGradeDao();
	}

	public static Component getItemCom(){
		new StuGradeSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnSelect){

			StudentGrade res=new StudentGrade();
			res.setSno(txtsno.getText().trim());
			res.setSname(txtSname.getText().trim());


			res.setCno(txtcno.getText().trim());

			res.setCname(txtCname.getText().trim());


			res.setTno(txtTno.getText().trim());

			res.setTname(txtTname.getText().trim());


			List<StudentGrade> list =  stuGradeDao.select(res);
			
			Object[][] r1=getSelect(list);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);

			String sql = stuGradeDao.selectSql(res);

			System.out.println(sql);
			sqlArea.setText(sql);
		}
	}

	Object[][] getSelect(List<StudentGrade> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			StudentGrade res=list.get(i);
			results[i][0]=res.getSno();
			results[i][1]=res.getSname();
			results[i][2]=res.getSsex();
			results[i][3]=res.getEntranceAge();
			results[i][4]=res.getEntranceYear();
			results[i][5]=res.getClazz();
			results[i][6]=res.getCno();
			results[i][7]=res.getCname();
			results[i][8]=res.getTno();
			results[i][9]=res.getTname();
			results[i][10]=res.getCredit();
			results[i][11]=res.getYear();
			results[i][12]=res.getScore();
		}

		return results;
	}


}
