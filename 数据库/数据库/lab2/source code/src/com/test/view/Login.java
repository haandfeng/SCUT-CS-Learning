package com.test.view;


import com.test.dao.StudentDao;
import com.test.dao.TeacherDao;
import com.test.dao.UserDao;
import com.test.pojo.Student;
import com.test.pojo.Teacher;
import com.test.pojo.User;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

class GlobalVals{
    static String user_id="";
}
public class Login extends JFrame {

   private JPanel contentPane;
   private JTextField jtf1;
   private JPasswordField jtf2;
    private JTextField txtValid,txtAnswer;
    private JLabel labValid,labType;
    private JComboBox cmbType;

    Dimension frameSize = new Dimension(450, 350);
    ImageIcon imageIcon = new ImageIcon(this.getClass().getResource(
            "/1.png"));


private static int validResult ;
private static Random random = new Random() ;


   /**
    * Create the frame.
    */
   public Login() {
       setTitle("Login Entrance");


       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       //setBounds(100, 100, 450, 350);
       setSize(frameSize);
       setLocationRelativeTo(null);

       contentPane = new JPanel();
       contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
       setContentPane(contentPane);
       contentPane.setLayout(null);



       
       JButton btnNewButton = new JButton("Reset");
       btnNewButton.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {
               jtf1.setText("");
               jtf2.setText("");
           }
       });
       btnNewButton.setFont(new Font("MS Song", Font.BOLD, 17));
       btnNewButton.setBounds(64, 260, 100, 25);
       contentPane.add(btnNewButton);
       JLabel jL1 = new JLabel("");
       jL1.setForeground(Color.RED);
       jL1.setBounds(126, 260, 100, 15);
       contentPane.add(jL1);
       
       JButton btnNewButton_1 = new JButton("Login");
       btnNewButton_1.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {
               try{
                   Integer result = Integer.valueOf(txtAnswer.getText());
                   if (result != validResult){
                       throw new Exception();
                   }
               }catch (Exception ex){
                   JOptionPane.showMessageDialog(null, "Incorrect verification code","Information",JOptionPane.INFORMATION_MESSAGE);
                   return;
               }


               String username=jtf1.getText();
               char password[]=jtf2.getPassword();
               String type = cmbType.getSelectedItem().toString();
               if ("Administrator".equals(type)){
                   UserDao userService=new UserDao();
                   User user=userService.selectUserByName(username);

                   if(user==null) {
                       JOptionPane.showMessageDialog(null, "Account not exist£°","Information",JOptionPane.INFORMATION_MESSAGE);

                   }else {
                       if(!user.getPassword().equals(String.valueOf(password))) {
                           JOptionPane.showMessageDialog(null, "Account or password not correct£°","Information",JOptionPane.INFORMATION_MESSAGE);
                       }else {
                           GlobalVals.user_id =username;
                           JOptionPane.showMessageDialog(null, "Login successfully£°","Information",JOptionPane.INFORMATION_MESSAGE);
                           dispose();

                           MainView main=new MainView(user);
                           main.setVisible(true);


                       }
                   }
               }else if ("Student".equals(type)){
                   StudentDao userService=new StudentDao();
                   Student stu=userService.selectBySno(username);

                   if(stu==null) {
                       JOptionPane.showMessageDialog(null, "Account does not exist£°","Information",JOptionPane.INFORMATION_MESSAGE);

                   }else {
                       if (!stu.getPassword().equals(String.valueOf(password))) {
                           JOptionPane.showMessageDialog(null, "The account or password incorrect£°", "Information", JOptionPane.INFORMATION_MESSAGE);
                       } else {
                           GlobalVals.user_id =username;
                           JOptionPane.showMessageDialog(null, "Login successfully£°", "Information", JOptionPane.INFORMATION_MESSAGE);
                           dispose();

                           StuView main = new StuView(stu);
                           main.setVisible(true);


                       }
                   }
               }else {
                   TeacherDao userService=new TeacherDao();
                   Teacher tea= userService.selectByTno(username);

                   if(tea==null) {
                       JOptionPane.showMessageDialog(null, "Account does not exist£°","Information",JOptionPane.INFORMATION_MESSAGE);

                   }else {
                       if (!tea.getPassword().equals(String.valueOf(password))) {
                           JOptionPane.showMessageDialog(null, "The account or password incorrect£°£°", "Information", JOptionPane.INFORMATION_MESSAGE);
                       } else {
                           GlobalVals.user_id =username;
                           JOptionPane.showMessageDialog(null, "Login successfully£°", "Information", JOptionPane.INFORMATION_MESSAGE);
                           dispose();

                           TeaView main = new TeaView(tea);
                           main.setVisible(true);


                       }
                   }


               }


               
           }
       });
       btnNewButton_1.setFont(new Font("MS Song", Font.BOLD, 17));
       btnNewButton_1.setBounds(257, 260, 100, 25);
       contentPane.add(btnNewButton_1);
       
       JLabel lblNewLabel = new JLabel("MIS");
       lblNewLabel.setFont(new Font("MS Song", Font.BOLD, 27));
       lblNewLabel.setBounds(120, 10, 300, 46);
       contentPane.add(lblNewLabel);
       
       JLabel lblNewLabel_1 = new JLabel("Acc:");
       lblNewLabel_1.setFont(new Font("MS Song", Font.BOLD, 18));
       lblNewLabel_1.setBounds(67, 86, 58, 21);
       contentPane.add(lblNewLabel_1);
       
       JLabel lblNewLabel_2 = new JLabel("Pas£∫");
       lblNewLabel_2.setFont(new Font("MS Song", Font.BOLD, 18));
       lblNewLabel_2.setBounds(67, 120, 58, 21);
       contentPane.add(lblNewLabel_2);

       labValid = new JLabel("Verify");
       labValid.setFont(new Font("MS Song", Font.BOLD, 18));
       labValid.setBounds(60, 170, 58, 21);
       contentPane.add(labValid);
       
       jtf1 = new JTextField();
       jtf1.setFont(new Font("MS Song", Font.BOLD, 18));
       jtf1.setBounds(126, 87, 228, 21);
       contentPane.add(jtf1);
       jtf1.setColumns(10);
       
       jtf2 = new JPasswordField();
       jtf2.setBounds(126, 120, 228, 21);
       contentPane.add(jtf2);


       //—È÷§¬Î
       txtValid = new JTextField();
       txtValid.setHorizontalAlignment(JTextField.RIGHT);

       txtValid.setFont(new Font("MS Song", Font.BOLD, 18));
       txtValid.setBounds(126, 170, 80, 21);
       contentPane.add(txtValid);
        txtValid.setText(getRandomNum());
        txtValid.setEditable(false);

       txtAnswer = new JTextField();

       txtAnswer.setFont(new Font("MS Song", Font.BOLD, 18));
       txtAnswer.setBounds(210, 170, 80, 21);
       contentPane.add(txtAnswer);

       JButton btnFlush = new JButton("Refresh");
       btnFlush.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {
               txtValid.setText(getRandomNum());
           }
       });
       btnFlush.setFont(new Font("MS Song", Font.BOLD, 17));
       btnFlush.setBounds(300, 170, 130, 21);
       contentPane.add(btnFlush);

       labType = new JLabel("User type£∫");
       labType.setFont(new Font("MS Song", Font.BOLD, 17));
       labType.setBounds(60, 220, 140, 21);
       contentPane.add(labType);

       cmbType = new JComboBox();

       cmbType.addItem("Administrator");
       cmbType.addItem("Teacher");
       cmbType.addItem("Student");

       cmbType.setBounds(160, 220, 130, 23);
       contentPane.add(cmbType);



       //setIconImage(imageIcon.getImage());

       addImageByJLable();

       setVisible(true);
       
   }

  public void addImageByJLable() {
    setLayout(null);
    // …Ë÷√±≥æ∞
    JLabel lbBg = new JLabel(imageIcon);
    lbBg.setBounds(0, 0, frameSize.width, frameSize.height);
    this.getContentPane().add(lbBg);
    setVisible(true);
  }


   public String getRandomNum(){
       StringBuilder build = new StringBuilder();
       int num1 = random.nextInt(10);
       build.append(num1);
       build.append("+");
       int num2 = random.nextInt(10);
       build.append(num2);
       validResult = num1 +num2;
       build.append("=");
       return build.toString();
   }
}
