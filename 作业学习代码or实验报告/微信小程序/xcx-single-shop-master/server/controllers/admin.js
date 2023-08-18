import {sequelize} from '../sql.js'

var qn = require('qn');
var rp = require('request-promise')


var moment = require('moment')
var client = qn.create({
    accessKey: 'MIn8z_veB2LIAFvJtTw5lwUQQxo2Otq8lk8w724r',
    secretKey: 'j02Smy4yGfggacjF1DE-Q5vl4Ae9pN3ovhLWP6F1',
    bucket: 'handsomebird',

});

//��̨����Ա��¼
let login =async(ctx,next)=>{
    let crb =ctx.request.body;
    let res = await (sequelize.query("select `userName`,`role` from admin where userName ='"+crb.userName+"' and password ='"+crb.password+"'",{
        type: sequelize.QueryTypes.SELECT
    }))
    if(res.length>0){
        return ctx.response.body={
            "code": 0,
            "msg": res[0],
        }
    }else{
        return ctx.response.body={
            "code": -2,
            "data":'�û������������',
        }
    }
}



//��ȡ�û��б�
let getUserList =async(ctx,next)=>{
    let res = await (sequelize.query("select * from user",{
        type: sequelize.QueryTypes.SELECT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res,
    }
}

//�����û�������
let searchByName = async(ctx,next)=>{
    let res = await (sequelize.query("select * from user where nickName  like '%"+ctx.query.name+"%'",{
            type: sequelize.QueryTypes.SELECT
        }))
    return ctx.response.body={
        "code":0,
        "msg":res,
    }

}



//��ȡ��̨�����б�
let getOrderList =async(ctx,next)=>{
    let count = await (sequelize.query("select count(*) as count  from `order`",{
        type: sequelize.QueryTypes.SELECT
    }))

    let res = await (sequelize.query("select * from `order` order by id desc limit "+ctx.query.page+","+ctx.query.pageSize,{
        type: sequelize.QueryTypes.SELECT
    }))
    res.forEach(item=>{
        item.cartList=JSON.parse(item.cartList)
        item.time = moment(item.time).format('YYYY-MM-DD HH:MM')
    })

    return ctx.response.body={
        "code":0,
        "data":{
            "count":count[0].count,
            "list":res
        },
    }

}

//��ȡ��̨ԤԼ�б�
let getAppointList =async(ctx,next)=>{
    let page=(ctx.query.page-1)*10

    let res = await (sequelize.query("select * from `appoint` limit "+page+",5",{
        type: sequelize.QueryTypes.SELECT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res,
    }

}

//��̨������ȡ��Ʒ����ҳ��
let getfoodList =async(ctx,next)=>{
    let count = await (sequelize.query("select count(*) as count  from foods where status=1",{
        type: sequelize.QueryTypes.SELECT
    }))
    let res = await (sequelize.query("select * from foods where status=1  order by id desc  limit "+ctx.query.page+","+ctx.query.pageSize,{
        type: sequelize.QueryTypes.SELECT
    }))
    //�˵��б�
    let menuMap = await (sequelize.query("select * from menu",{
        type: sequelize.QueryTypes.SELECT
    }))
    let map={}
    menuMap.forEach(function(item){
        map[item.id]=item.type
    })

    return ctx.response.body={
        "code":0,
        "data":{
            "count":count,
            "foods":res,
            "menuMap":map
        },
    }
}

//��̨��Ӳ�Ʒ
let addFood =async(ctx,next)=>{
    //���ܵĲ���
    let crb=ctx.request.body;
    let res = await (sequelize.query("INSERT INTO `foods` (`type`,`name`,`price`,`img`,`enName`,`status`,`tem`,`size`,`desc`) VALUES" +
        " ('"+crb.type+"','"+crb.name+"','"+crb.price+"','"+crb.img+"','"+crb.enName+"',1,'"+crb.tem+"','"+crb.size+"','"+crb.desc+"')",{
        type: sequelize.QueryTypes.INSERT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res,
    }
}

//���²�Ʒ
let updateFood =async(ctx,next)=>{
    let crb=ctx.request.body;
    let res = await (sequelize.query("UPDATE  `foods` SET  `name`='"+crb.name+"',`price`='"+crb.price+"', `img`='"+crb.img+"'," +
        " `type`='"+crb.typeId+"', `enName`='"+crb.enName+"', `size`='"+crb.size+"', `tem`='"+crb.tem+"', `desc`='"+crb.desc+"' where id='"+crb.id+"'",{
        type: sequelize.QueryTypes.UPDATE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"���ĳɹ�",
        "data":res
    }
}

//��ȡ�����û���Ϣ
let getUserInfo =async(ctx,next)=>{
    let res = await (sequelize.query("select * from user where userName='"+ctx.query.userName+"'",{
        type: sequelize.QueryTypes.SELECT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res[0],
    }
}



//�޸��û�Ȩ��
let updateRole =async(ctx,next)=>{
    let crb=ctx.request.body;
    let res = await (sequelize.query("UPDATE  user SET `role`='"+crb.role+"' , `root`='"+crb.root+"' where id='"+crb.id+"'",{
        type: sequelize.QueryTypes.UPDATE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"���ĳɹ�",
        "data":res
    }
}





//ɾ���û�
let deleteUser =async(ctx,next)=>{
    let res = await (sequelize.query("DELETE FROM `users` WHERE `username` = '"+ctx.query.username+"'",{
        type: sequelize.QueryTypes.DELETE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"ɾ���ɹ�",
    }
}


//��̨ɾ����Ʒ
let deleteFood=async(ctx,next)=>{
    let res = await (sequelize.query("UPDATE  `foods` SET `status`=0  WHERE `id` = '"+ctx.query.id+"'",{
        type: sequelize.QueryTypes.UPDATE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"ɾ���ɹ�",
    }
}

//��ȡʳƷ�����б�
let getFoodTypeList =async(ctx,next)=>{
    let res = await (sequelize.query("select * from menu",{
        type: sequelize.QueryTypes.SELECT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res,
    }
}

//���ʳƷ����
let addMenu =async(ctx,next)=>{
    //���ܵĲ���
    let crb=ctx.request.body;
    let res = await (sequelize.query("INSERT INTO `menu` (`type`) VALUES ('"+crb.type+"')",{
        type: sequelize.QueryTypes.INSERT
    }))

    return ctx.response.body={
        "code":0,
        "msg":res,
    }
}

//��ȡͼƬ���    
let getImgNum =async(ctx,next)=>{
    let res = await (sequelize.query("select `img` from  `foods`  where type='"+ctx.query.type+"' order by id desc  limit 0,1",{
        type: sequelize.QueryTypes.SELECT
    }))
    let num =  res.length>0?parseInt(res[0].img)+1:1;


    return ctx.response.body={
        "code":0,
        "msg":num,
    }
}
//����ʳƷ���ƽ�������
let searchFoodsByName= async(ctx,next)=>{
    let res = await (sequelize.query("select * from `foods` where name  like '%"+ctx.query.name+"%'",{
        type: sequelize.QueryTypes.SELECT
    }))
    return ctx.response.body={
        "code":0,
        "msg":res,
    }
};


//��ɶ���
let overOrder= async(ctx,next)=>{
    let res = await (sequelize.query("UPDATE  `order` SET `status`=2  where orderId='"+ctx.query.orderId+"'",{
        type: sequelize.QueryTypes.UPDATE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"���ĳɹ�",
        "data":res
    }
};

//�˿��
let  refundOrder= async(ctx,next)=>{
    let res = await (sequelize.query("UPDATE  `order` SET `status`=0  where orderId='"+ctx.query.orderId+"'",{
        type: sequelize.QueryTypes.UPDATE
    }))
    return ctx.response.body={
        "code":0,
        "msg":"���ĳɹ�",
        "data":res
    }
};


//��ӡ�սᵥ
let printDay= async(ctx,next)=>{
    let day = new Date();
    let dayEnd= moment(day).add(1, 'days').format('YYYY-MM-DD 00:00:00');
    let dayBegin = moment(day).format('YYYY-MM-DD 00:00:00');
    let orderNumber = await (sequelize.query("select count(*) as count  from `order`  where  status =2 AND time BETWEEN '"+dayBegin+"' AND '"+dayEnd+"' ",{
        type: sequelize.QueryTypes.SELECT
    }))
    console.log(orderNumber)
    let sum = await (sequelize.query("select SUM(`sumMoney`) as count  from `order`  where  status =2 AND time BETWEEN '"+dayBegin+"' AND '"+dayEnd+"' ",{
        type: sequelize.QueryTypes.SELECT
    }))
    let xsum = sum[0].count?sum[0].count:0;
    let xorderNumber = orderNumber[0].count?orderNumber[0].count:0;
     let option={
        method:'POST',
        uri: "https://open-api.10ss.net/print/index",
        formData:{
            "client_id":"1046493438",
            "access_token":"dd2a129ebd1f4ff2855a321ad2b210cc",
            "sign":"c38037c0b3951e95f01f815944b43e36",
            "content":"\r" +"\r" +"\r" +"\r" +
            "@@2<FH2><center>֧�����ӵ�</center></FH2>"+ "\r" +
            "@@2�豸���:4004559796"+"\r" +
            "@@2�ϴν���:"+dayBegin+"\r" +
            "@@2���ؽ���:"+dayEnd+"\r" +
            "@@2--------------------------------"+"\r" +
            "<table><tr><td>֧����ʽ</td><td>֧��ʱ��</td><td>֧�����</td></tr></table>"+
            "@@2--------------------------------"+"\r" +
            "@@2��������֧����ʽ����ͳ�ƣ�������"+"\r" +
            "<LR>΢��,��"+xsum+"</LR>"+"\r" +
            "������"+xorderNumber+"\r" +
            "@@2--------------------------------"+"\r" +
            "@@2�ϼƽ�"+xsum+"\r" +
            "@@2�ϼƱ�����"+xorderNumber+"\r",
            "timestamp":"1526124538",
            "id":"3F2504E0-4F89-11D3-9A0C-0305E82C3312",
            "machine_code":"4004559796",
            "origin_id":"2018050920444247"
        },
        json:true
    }
    let result = await rp(option)

    return ctx.response.body={
        "code":0,
        "data":result
    }
}





module.exports = {
    'POST /admin/login':login,//����Ա��¼
    'GET /admin/getAppointList':getAppointList,//��ȡ��̨ԤԼ�б�
    'POST /admin/addFood':addFood,
    'POST /admin/updateRole': updateRole,
    'POST /admin/updateFood': updateFood,
    'GET /admin/getUserInfo': getUserInfo,
    'GET /admin/deleteUser': deleteUser,
    'GET /admin/getUserList': getUserList,
    'GET /admin/deleteFood': deleteFood,
    'GET /admin/searchFoodsByName':searchFoodsByName,//����ʳƷ���ƽ�������
    'GET /admin/getfoodList': getfoodList,
    'GET /admin/getOrderList': getOrderList,//��̨��ȡ�����б�
    'GET /admin/searchByName':searchByName,//�������������û�
    'GET /admin/getFoodTypeList':getFoodTypeList,//��ȡʳƷ�����б�
    'POST /admin/addMenu':addMenu,//���ʳƷ����
    'GET /admin/getImgNum':getImgNum, //��ȡͼƬ���
    'GET /admin/overOrder':overOrder, //��ɶ���
    'GET /admin/refundOrder':refundOrder, //�˿��
    'GET /admin/printDay':printDay//��ӡ�սᵥ
}