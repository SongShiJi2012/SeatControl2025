%% Create enSeatHightMotorRunsts enum

classdef enSeatHightMotorRunsts < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_DnBkRelayAdhesion_FU(1)
        EN_ManualAdjust_FU(2)
        EN_AutoAdjust_FU(3)
        EN_DnBkRelayAdhesion_FU_Stop(4)
        EN_ManualAdjust_FU_Stop(5)
        EN_AutoAdjust_FU_Stop(6)
        EN_DnFURelayAdhesion_BK(7)
        EN_ManualAdjust_BK(8)
        EN_AutoAdjust_BK(9)
        EN_DnFURelayAdhesion_BK_Stop(10)
        EN_ManualAdjust_BK_Stop(11)
        EN_AutoAdjust_BK_Stop(12)
        EN_AutoAdjust_FUSuccess_Stop(13)
        EN_AutoAdjust_BKSuccess_Stop(14)
        EN_Timeout_Stop(15)
        EN_UpFn_Lock_Stop(16)
        EN_DnBa_Lock_Stop(17)
        EN_UpFn_Hall_Stop(18)
        EN_DnBa_Hall_Stop(19)
        EN_UpFn_MovTypeChange(20)
        EN_DnBa_MovTypeChange(21)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatHightMotorRunsts.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '����������ͣ�&#10;0���޶�����&#10;1���̵����º�ճ��������ǰ�ƶ���&#10;2���ֶ�������Ч��ǰ�ƶ���&#10;3���Զ�������Ч��ǰ�ƶ���&#10;4���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��&#10;5.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;6.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ&#10;7.�̵�����ǰճ�������º��ƶ�&#10;8���ֶ�������Ч��ǰ�ƶ���&#10;9���Զ�������Ч��ǰ�ƶ���&#10;A���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��&#10;B.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;C.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;D.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ&#10;E.�Զ����ڿ�����Ч�º��ƶ�ֹͣ&#10;F.��ʱֹͣ&#10;10.���϶�ת����ֹͣ&#10;11.���¶�ת����ֹͣ&#10;12.���ϻ�������ֹͣ&#10;13.���»�������ֹͣ,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
