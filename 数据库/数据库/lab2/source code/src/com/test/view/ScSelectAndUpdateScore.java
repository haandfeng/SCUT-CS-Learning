package com.test.view;


import com.test.dao.CourseDao;
import com.test.dao.ScDao;
import com.test.dao.StudentDao;
import com.test.dao.TeacherDao;
import com.test.pojo.Course;
import com.test.pojo.Sc;
import com.test.pojo.Student;
import com.test.pojo.Teacher;
//import java.test.view.Login;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ScSelectAndUpdateScore extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,scPane;



	private JTextField txtId,txtScore;

	private JLabel labId,labScore;

	private JButton btnModify,btnSelect;


	private JTable table;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	private StudentDao studentDao ;
	private TeacherDao teacherDao ;
	private ScDao scDao ;

	static String[] colSno= {"SCID","ID","CID","Instructor ID","Year","Score"};


	public ScSelectAndUpdateScore(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnModify=new JButton("Score");
		btnSelect=new JButton("Search");

		btnSelect.addActionListener(this);
		btnModify.addActionListener(this);



		btnPanel.add(btnSelect);
		btnPanel.add(btnModify);
		panel.add(btnPanel,BorderLayout.NORTH);

		centerPanel=new JPanel();
		selectResultPane=new JPanel();


		table=new JTable();
		scrollPane=new JScrollPane(table);

		Object[][] r1=getSelect(scDao.selectAll());

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		scPane=new JPanel(new GridLayout(5,4));

		labId=new JLabel("SCID");
		labScore=new JLabel("Score");

		txtId=new JTextField(15);
		txtScore=new JTextField(15);


		scPane.add(labId);
		scPane.add(txtId);
		scPane.add(labScore);
		scPane.add(txtScore);



		centerPanel.add(scPane);
		centerPanel.add(selectResultPane);

		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		courseDao = new CourseDao();
		studentDao = new StudentDao();
		teacherDao = new TeacherDao();
		scDao = new ScDao();
	}

	public static Component getItemCom(){
		new ScSelectAndUpdateScore();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){




		if(e.getSource()==btnModify){
			String id=txtId.getText().trim();

			Sc sc = scDao.selectId(id);
			if (sc == null){
				JOptionPane.showMessageDialog(null, "Student selection information does not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			try{
				Integer score = Integer.valueOf(txtScore.getText().trim());

				sc.setScore(score);

			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Revision failed, please enter a valid course number","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}


			int i=scDao.updateScore(sc);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				Object[][] r1=getSelect(scDao.selectAll());

				table=new JTable(r1,colSno);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}

		if(e.getSource()==btnSelect){


			Sc sc = new Sc();

			try{
				Integer id = Integer.valueOf(txtId.getText().trim());

				sc.setId(id);


			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Revision failed, please enter a valid SCID","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}


			List<Sc> scList =  scDao.select(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);

		}
	}

	Object[][] getSelect(List<Sc> list){


		Object[][] results=new Object[list.size()][colSno.length];
		int j= 0;
		for(int i=0;i<list.size();i++){
			Sc sc=list.get(i);
			String tno =sc.getTno();
//			System.out.println(tno);
//			System.out.println(GlobalVals.user_id);
			if (tno.equals(GlobalVals.user_id)){
				results[j][0]=sc.getId();
				results[j][1]=sc.getSno();
				results[j][2]=sc.getCno();
				results[j][3]=tno;
				results[j][4]=sc.getYear();
				if (sc.getScore() != null){
					results[j][5]=sc.getScore();
				}
				j+=1;
			}

		}

		return results;
	}


}
