<?php
// 全局中间件定义文件
use app\CrossDomain;
use think\middleware\AllowCrossDomain;

return [
    // 全局请求缓存
    // \think\middleware\CheckRequestCache::class,
    // 多语言加载
    // \think\middleware\LoadLangPack::class,
    // Session初始化
    // \think\middleware\SessionInit::class

    CrossDomain::class,// 跨域
    // 跨域
    AllowCrossDomain::class,
];
